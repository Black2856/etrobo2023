/*
 * クラス名:RearCamera
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#ifndef REARCAMERA_H
#define REARCAMERA_H

#include <opencv2/opencv.hpp>

class RearCamera {
public:
    // インスタンス取得
    static RearCamera& getInstance();

    /**
     * カメラを起動する
     * @retval true  起動成功 or 起動済み
     * @retval false 起動失敗
     */
    bool start();
    void stop();
    // 写真を撮影
    void takePhoto();
    bool savePhoto(const char* filePath);

private:

    RearCamera(); // プライベートコンストラクタ
    ~RearCamera();
    static RearCamera* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    RearCamera(RearCamera const&);
    void operator=(RearCamera const&);

    // カメラオブジェクト
    cv::VideoCapture capture;

    cv::Mat img;

};

#endif  // REARCAMERA_H