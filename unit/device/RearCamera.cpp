/*
 * クラス名:RearCamera
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#include "RearCamera.h"
#include "setting.h"

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
            return false;
        }
    }
    return true;
}

void RearCamera::stop() {
    if (capture.isOpened()) {
        // カメラを解放する
        capture.release();
    }
}

cv::Mat RearCamera::takePhoto() {
    cv::Mat frame;
    capture.read(frame); // カメラからフレームを読み取る
    return frame;
}