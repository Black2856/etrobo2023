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
}

RearCamera& RearCamera::getInstance() {
    if (!instance) {
        instance = new RearCamera();
    }
    return *instance;
}

cv::Mat RearCamera::takePhoto(const char* fileName) {
    // カメラの起動
    cv::VideoCapture capture(CAMERA_NUMBER);
    cv::Mat img;
    if (capture.isOpened()) {
        printf("カメラの起動に成功しました。\n");
    } else {
        printf("カメラの起動に失敗しました。\n");
        return img;
    }
    // カメラからフレームを読み取る
    capture.read(img);
    if (img.empty()) {
        printf("フレームをキャプチャできませんでした。\n");
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