#include "RearCamera.h"
#include "setting.h"
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>

int main() {
    // 停止する時間（ミリ秒単位）
    int millisecondsToSleep = 500; // 0.5秒

    RearCamera& camera = RearCamera::getInstance();
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
        while (std::getline(file, line)) { // ファイルから一行ずつ読み込む
            // 現在のシステム時刻を取得
            auto currentTime = std::chrono::system_clock::now();

            // エポックからの経過時間を取得
            auto duration = currentTime.time_since_epoch();

            // ミリ秒単位で変換
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

            const int bufferSize = 25 + IMG_FILENAME_LEN;
            char buffer[bufferSize];
            std::snprintf(buffer, bufferSize, "%s_%ld", line.c_str(), milliseconds.count());

            camera.takePhoto();
            // 現在時刻ミリ秒のファイル名で保存
            camera.savePhoto(buffer);
        }

        camera.stop();

        file.close(); // ファイルを閉じる
        // ファイルを削除する
        std::remove(IMG_QUEUE_PATH);

    }
        
    return 0;
}