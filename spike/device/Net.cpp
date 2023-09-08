/*
 * クラス名:Net
 * 作成日:2023/09/08
 * 作成者:杉本
 */
#include "Net.h"
#include "setting.h"
#include <stdlib.h>
#include <stdio.h>

Net::Net() :
    context(1),
    socket(context, ZMQ_REQ) {}

Net::~Net() {
    close();
}

Net& Net::getInstance() {
    if (!instance) {
        instance = new Net();
    }
    return *instance;
}

bool Net::open() {
    // サーバーアドレスを設定して接続
    try {
        socket.connect(PC_ADDRESS);
    } catch (const std::exception& e) {
        printf(PC_ADDRESS "に接続できません。\n");
        return false;
    }
    return true;
}

bool Net::sendImage(cv::Mat image) {
    // 画像情報を設定
    int32_t imageInfo[] = [
        static_cast<int32_t>(image.rows),
        static_cast<int32_t>(image.cols),
        static_cast<int32_t>(image.type())
    ];

    // 画像情報を送信
    for (int i = 0; i < 3; i++) {
        zmq::message_t msg((void*)&imageInfo[i], sizeof(int32_t), NULL);
        if(!socket.send(msg, ZMQ_SNDMORE)) {
            printf("画像情報の送信に失敗しました。\n");
            return false;
        }
    }

    // 画像データを設定
    void* imageData = malloc(image.total() * image.elemSize());
    memcpy(imageData, image.data, image.total() * image.elemSize());

    // 画像データを送信
    zmq::message_t msg2(imageData, imageInfo[0] * imageInfo[1] * imageInfo[2], my_free, NULL);
    if(!socket.send(msg2)) {
        printf("画像データの送信に失敗しました。\n");
        // メモリを解放
        free(imageData);
        return false;
    }
    // メモリを解放
    free(imageData);
    return true;
}

void Net::close() {
    // ソケットを閉じる
    socket.close();
}