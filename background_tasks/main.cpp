#include "Signal.h"
#include "setting.h"
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <opencv2/opencv.hpp>

// ../spike/device/Signal.h
Signal recvSignal(RECV_PORT);
Signal sendSignal(SEND_PORT);

cv::Mat take(const char* fileName) {
    // カメラの起動
    cv::VideoCapture capture(CAMERA_NUMBER);
    cv::Mat img;
    if (capture.isOpened()) {
        printf("カメラの起動に成功しました。\n");
    } else {
        printf("カメラの起動に失敗しました。\n");
        capture.release();
        return img;
    }
    // カメラからフレームを読み取る
    capture.read(img);
    if (img.empty()) {
        printf("フレームをキャプチャできませんでした。\n");
        capture.release();
        return img;
    }

    // カメラを解放する
    capture.release();
    printf("カメラを正常終了しました。。\n");

    // 画像を保存する
    char path[150];
    sprintf(path, IMG_PATH "%s", fileName);
    if(!cv::imwrite(path, img)) {
        printf("画像の保存に失敗しました。\n");
    }
    return img;
}

bool takePhoto(RearCamera& camera, Signal& signal) {
    // ファイルを開く
    std::ifstream inputFile(IMG_QUEUE_PATH);
    // ファイルが存在しない場合
    if (!inputFile) {
        return false;
    }

    std::string line;
    while (inputFile >> line) {
        // 撮影
        cv::Mat img = camera.takePhoto(line.c_str());

        // 画像が撮影できていない場合
        while (img.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SEND_CYCLE));
            printf("Retry\n");
            img = camera.takePhoto(line.c_str());
        }
        // PCへ送信
        signal.sendImage(img, line.c_str());
    }

    // 内容を破棄、新しい空のファイルを作成
    std::ofstream outputFile(IMG_QUEUE_PATH, std::ios::trunc);

    // ファイルが正しく開けたか確認
    if (outputFile) {
        printf("撮影待機リストを初期化しました。");
    } else {
        printf("撮影待機リストの初期化に失敗しました。");
    }
    // ファイルを閉じる
    outputFile.close();
    inputFile.close();

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