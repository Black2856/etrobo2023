/*
 * クラス名:Net
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#include "Net.h"
#include "setting.h"
#include <sys/socket.h>
#include <vector>
#include <iostream>

Net* Net::instance = NULL;

Net::Net():
    clientSocket(socket(AF_INET, SOCK_STREAM, 0)) {
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(PC_IP_ADDRESS);
        serverAddress.sin_port = htons(PC_PORT);
    }

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
    if (
        connect(
            this->clientSocket,
            reinterpret_cast<sockaddr*>(&this->serverAddress),
            sizeof(this->serverAddress)
        ) == -1
    ) {
        close(this->clientSocket);
        return false;
    }
}

void Net::close() {
    // ソケットを閉じる
    close(this->clientSocket);
}

bool Net::sendImage(cv::Mat image) {
    // 画像データを一時的に格納するバッファ
    std::vector<uchar> buffer;
    // フレームをバッファにエンコード
    cv::imencode(".jpg", image, buffer);

    // 画像データのサイズを先に送信
    size_t bufferSize = buffer.size();
    if (send(this->clientSocket, &bufferSize, sizeof(bufferSize), 0) == -1) {
        return false;
    }

    // 画像データを送信
    if (send(this->clientSocket, buffer.data(), buffer.size(), 0) == -1) {
        return false;
    }

    return true;
}