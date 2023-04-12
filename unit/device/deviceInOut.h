#ifndef DEVICE_IN_OUT_H
#define DEVICE_IN_OUT_H

#include "SonarSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "Clock.h"

class deviceInOut{ //deviceのSingleton管理クラス
public:
    // インスタンス取得
    static deviceInOut& getInstance();

    // シングルトンであるため、コピーおよび代入演算子は禁止
    deviceInOut(deviceInOut const&)    = delete;
    void operator=(deviceInOut const&) = delete;

    // 各種インスタンス
    ev3api::SonarSensor sonarSensor;
    ev3api::TouchSensor touchSensor;
    ev3api::GyroSensor  gyroSensor;
    ev3api::ColorSensor colorSensor;
    ev3api::Motor       leftWheel;
    ev3api::Motor       rightWheel;
    ev3api::Clock       clock;

private:
    deviceInOut(); // プライベートコンストラクタ
    static deviceInOut* instance; // シングルトンオブジェクトへのポインタ
};

#endif  // DEVICE_IN_OUT_H