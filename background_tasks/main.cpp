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
    // ファイルを開く
    std::ifstream file(IMG_QUEUE_PATH);
    // ファイルが存在しない場合
    if (!file) {
        return false;
    }

    std::string line;
    // ファイルから一行ずつ読み込む
    while (std::getline(file, line)) {
        // 撮影
        cv::Mat img = camera.takePhoto(line.c_str());
        // PCへ送信
        signal.sendImage(img, line.c_str());
    }
    // ファイルを閉じる
    file.close();
    // ファイルを削除する
    std::remove(IMG_QUEUE_PATH);
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
    // カメラを起動
    // カメラの起動に失敗した場合
    while (!camera.start()) {
        // 1秒待機
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    // 接続開始
    printf("Connect recv\n");
    recvSignal.connect_s();
    printf("Connect send\n");
    sendSignal.connect_s();

    std::thread recvThread(recv_m);
    std::thread sendThread(send_m);
    
    recvThread.join();
    sendThread.join();

    recvSignal.close_s();
    sendSignal.close_s();

    camera.stop();
    return 0;
}