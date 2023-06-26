#ifndef SETTINGS_H
#define SETTINGS_H

// デバイスのポート設定
#define SONAR_SENSOR PORT_3
#define TOUCH_SENSOR PORT_1
#define GYRO_SENSOR PORT_4
#define COLOR_SENSOR PORT_2
#define LEFT_WHEEL PORT_C
#define RIGHT_WHEEL PORT_B

// デバイス設定
#define TIRE_DIAMETER 100.0 // タイヤ直径（mm）
#define TREAD 126.0 // 車体トレッド幅（mm）
#define CAMERA_NUMBER 0 // カメラデバイス番号（通常は0）を指定する
#define CYCLE 1000 * 10 // 処理周期(msec)

#endif  // SETTINGS_H