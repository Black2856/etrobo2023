#include "RearCamera.h"
#include "Signal.h"
#include "setting.h"
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    // 停止する時間（ミリ秒単位）
    int millisecondsToSleep = 500; // 0.5秒

    // ../spike/device/RearCamera.h
    RearCamera& camera = RearCamera::getInstance();
    // ../spike/device/Signal.h
    Signal& signal = Signal::getInstance();
    // 接続開始
    printf("Connect Start\n");
    signal.connect_s();

    while (true) {
        // 一定時間停止する
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToSleep));
        // ファイルを開く
        std::ifstream file(IMG_QUEUE_PATH);
        // ファイルが存在しない場合
        if (!file) {
            continue;
        }
        // カメラの起動に失敗した場合
        if (!camera.start()) {
            continue;
        }

        std::string line;
        // ファイルから一行ずつ読み込む
        while (std::getline(file, line)) {
            // 撮影
            cv::Mat img = camera.takePhoto(line.c_str());
            // PCへ送信
            signal.sendImage(img, line.c_str())
        }
        camera.stop();
        // ファイルを閉じる
        file.close();
        // ファイルを削除する
        std::remove(IMG_QUEUE_PATH);
    }

    signal.close_s();
    return 0;
}