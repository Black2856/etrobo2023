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

    // カメラを起動
    // カメラの起動に失敗した場合
    while (!camera.start()) {
        // 1秒待機
        std::this_thread::sleep_for(std::chrono::milliseconds(SEND_CYCLE));
    }

    std::string line;
    // ファイルから一行ずつ読み込む
    while (std::getline(file, line)) {
        // 撮影
        cv::Mat img = camera.takePhoto(line.c_str());
        // 画像が撮影できていない場合
        while (img.empty()) {
            printf("Retry\n");
            img = camera.takePhoto(line.c_str());
        }
        // PCへ送信
        signal.sendImage(img, line.c_str());
    }
    // ファイルを閉じる
    file.close();
    camera.stop();
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