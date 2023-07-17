#ifndef SETTINGS_H
#define SETTINGS_H

// MAKE_SIMが定義されていた場合シミュレータ環境

// spikeポート設定
#define SONAR_SENSOR PORT_3
#define TOUCH_SENSOR PORT_1
#define GYRO_SENSOR PORT_4
#define COLOR_SENSOR PORT_2
#define LEFT_WHEEL PORT_C
#define RIGHT_WHEEL PORT_B

// spike設定
#define TIRE_DIAMETER 100.0 // タイヤ直径（mm）
#define TREAD 126.0 // 車体トレッド幅（mm）
#define CAMERA_NUMBER 0 // カメラデバイス番号（通常は0）を指定
#define CYCLE 1000 * 10 // 処理周期(msec)
#define IMG_PATH "img/" // 画像保存先path
#define IMG_QUEUE_PATH "Queue.txt" // 撮影待機リスト

// PC設定
#define PC_IP_ADDRESS "" // 受信時IPアドレス
#define PC_PORT 80 // 受信時port番号


#endif  // SETTINGS_H