/*
 * クラス名:RearCamera
 * 作成日:2023/05/12
 * 作成者:杉本
 * g++ RearCamera.c -o takephoto -I/usr/include/opencv4/ -lopencv_core -lopencv_videoio -lopencv_imgcodecs
 */

#include <opencv2/opencv.hpp>
#include "setting.h"

bool start(cv::VideoCapture& capture) {
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

void stop(cv::VideoCapture& capture) {
    if (capture.isOpened()) {
        // カメラを解放する
        capture.release();
    }
}

cv::Mat takePhoto(cv::VideoCapture& capture) {
    cv::Mat frame;
    capture.read(frame); // カメラからフレームを読み取る
    return frame;
}

bool savePhoto(const char* filePath, cv::Mat& photo) {
    // 画像を保存する
    bool success = cv::imwrite(filePath, photo);
  
    // 保存に成功したかどうかを返す
    return success;
}

int main(int argc, char* argv[]) {
    // カメラオブジェクト
    cv::VideoCapture capture;

    // 起動失敗した場合
    if (!start(capture)) {
        printf("カメラの起動に失敗しました。\n");
        return 1;
    }

    for(int i = 1; i < argc; ++i) {
        cv::Mat photo = takePhoto(capture);
        
        if (savePhoto(argv[i], photo)) {
            printf("画像を保存しました: %s\n", argv[i]);
        } else {
            printf("画像の保存に失敗しました: %s\n", argv[i]);
        }
    }

    stop(capture);

    return 0;
}
