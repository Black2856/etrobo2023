/*
 * クラス名:RearCamera
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#include "RearCamera.h"
#include "setting.h"
#include <stdio.h>

RearCamera* RearCamera::instance = NULL;

RearCamera::RearCamera() {
}

RearCamera::~RearCamera() {
    stop();
}

RearCamera& RearCamera::getInstance() {
    if (!instance) {
        instance = new RearCamera();
    }
    return *instance;
}

bool RearCamera::start() {
    if (!capture.isOpened()) {
        // カメラをオープンする
        capture.open(CAMERA_NUMBER); 

        // カメラがオープンできなかった場合
        if (!capture.isOpened()) {
            printf("カメラの起動に失敗しました。\n");
            return false;
        }
    }
    printf("カメラの起動に成功しました。\n");
    return true;
}

void RearCamera::stop() {
    if (capture.isOpened()) {
        // カメラを解放する
        capture.release();
        printf("カメラを正常終了しました。。\n");
    }
}

void RearCamera::takePhoto() {
    capture.read(this->img); // カメラからフレームを読み取る
}

bool RearCamera::savePhoto(const char* fileName) {
    // 画像を保存する
    char path[150];
    sprintf(path, IMG_PATH "%s", fileName);
    bool success = cv::imwrite(path, this->img);
  
    // 保存に成功したかどうかを返す
    return success;
}