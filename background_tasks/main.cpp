#include "RearCamera.h"
#include "setting.h"
#include <cstdio>
#include <stdio.h>
#include <chrono>
#include <thread>

int main() {
    // 停止する時間（ミリ秒単位）
    int millisecondsToSleep = 500; // 2秒

    RearCamera& camera = RearCamera::getInstance();
    FILE *fp;
    while (true) {
        fp = fopen(IMG_QUEUE_PATH,"r");
        // ファイルが存在した場合
        if(fp != NULL){
            // 現在のシステム時刻を取得
            auto currentTime = std::chrono::system_clock::now();

            // エポックからの経過時間を取得
            auto duration = currentTime.time_since_epoch();

            // ミリ秒単位で変換
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

            const int bufferSize = 20;
            char buffer[bufferSize];
            std::snprintf(buffer, bufferSize, "%ld", milliseconds.count());

            if (camera.start()) {
                camera.takePhoto();
                // 現在時刻ミリ秒のファイル名で保存
                camera.savePhoto(buffer);
            }
        } else {
            // ファイルを削除する
            std::remove(IMG_QUEUE_PATH);
        }
        camera.stop();
        // 一定時間停止する
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsToSleep));
    }
    return 0;
}