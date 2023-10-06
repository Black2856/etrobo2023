#include "RearCamera.h"
#include "Signal.h"
#include "setting.h"
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <opencv2/opencv.hpp>

// ../spike/device/RearCamera.h
RearCamera& camera = RearCamera::getInstance();
// ../spike/device/Signal.h
Signal recvSignal(RECV_PORT);
Signal sendSignal(SEND_PORT);

bool takePhoto(RearCamera& camera, Signal& signal) {
    // 静的変数定義（関数初回呼び出し時に一度だけ初期化される）
    static std::string name_prev = "exe.png";
    static cv::Mat img_prev = cv::imread("/home/robo/work/RasPike/sdk/workspace/" + name_prev);

    // ファイルを開く
    std::ifstream file(IMG_QUEUE_PATH);
    // ファイルが存在しない場合
    if (!file) {
        file.close();
        return false;
    }

    std::string line;
    int lineCount = 0;
    while (file >> line) {
        lineCount++;
        // 撮影
        cv::Mat img = camera.takePhoto(line.c_str());
        // 撮影失敗時
        if (img.empty()) {
            // 直前に撮影したものを送信
            signal.sendImage(img_prev, name_prev.c_str());
        } else { // 撮影成功時
            signal.sendImage(img, line.c_str());
            img_prev = img;
            name_prev = line;
        }
    }
    file.close();
    if(lineCount <= 0) {
        return false;
    }

    // ファイルを削除する
    std::remove(IMG_QUEUE_PATH);
    // ファイルを新規作成
    std::ofstream newFile(IMG_QUEUE_PATH);
    newFile.close();

    return true;
}

void recv_m() {
    // 10回受信したら終了
    for(int i = 0; i < 10; ++i) {
        recvSignal.recvFile();
        // 一定時間停止する
        std::this_thread::sleep_for(std::chrono::milliseconds(RECV_CYCLE));
    }
}

void send_m() {
    // 10枚撮影したら終了
    int i = 0;
    while(i < 10) {
        if(takePhoto(camera, sendSignal)) {
            i += 1;
        }
        // 一定時間停止する
        std::this_thread::sleep_for(std::chrono::milliseconds(SEND_CYCLE));
    }
}

int main() {
    // 接続開始
    printf("Connect recv\n");
    while (!recvSignal.connect_s()) {
        // 一定時間停止する
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    printf("Connect send\n");
    while (!sendSignal.connect_s()) {
        // 一定時間停止する
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::thread recvThread(recv_m);
    std::thread sendThread(send_m);
    
    recvThread.join();
    sendThread.join();

    recvSignal.close_s();
    sendSignal.close_s();

    return 0;
}