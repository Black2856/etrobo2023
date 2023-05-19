/*
 * クラス名:DeviceInOut
 * 作成日：2023/04/12
 * 作成者:杉本
 * 修正日:2023/05/19
 * 修正者:杉本
 * ver:2.0.0
 */

#ifndef DEVICE_IN_OUT_H
#define DEVICE_IN_OUT_H

#include "SonarSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "Clock.h"

class DeviceInOut{ //deviceのSingleton管理クラス
public:
    // インスタンス取得
    static DeviceInOut& getInstance();

// sonar
    int16_t     sonar_getDistance();

// touch
    bool        touch_isPressed();

// gyro
    int16_t     gyro_getAngle();
    void        gyro_reset();

// color
    //センサのモード切替に10~100msec程度かかるので頻繁な切替は非推奨
    int8_t      color_getBrightness();
    rgb_raw_t   color_getRawColor();

// LWheel
    int32_t     LWheel_getCount();
    void        LWheel_setPWM(int pwm);
    void        LWheel_stop();

// RWheel
    int32_t     RWheel_getCount();
    void        RWheel_setPWM(int pwm);
    void        RWheel_stop();

// clock
    void        clock_reset();
    uint64_t    clock_now();
    void        clock_sleep(uint64_t duration); // usec
    void        clock_wait(uint64_t duration);  // usec

// battery
    int         battery_getCurrent(); // 電流取得(mA)
    int         battery_getVoltage(); // 電圧取得(mV)

// button
    // 下記3種のみ使用可
    // LEFT_BUTTON  = 0
    // RIGHT_BUTTON = 1
    // ENTER_BUTTON = 4
    bool        button_isPressed(button_t button);


private:
    // 各種インスタンス
    ev3api::SonarSensor sonarSensor;
    ev3api::TouchSensor touchSensor;
    ev3api::GyroSensor  gyroSensor;
    ev3api::ColorSensor colorSensor;
    ev3api::Motor       leftWheel;
    ev3api::Motor       rightWheel;
    ev3api::Clock       clock;

    DeviceInOut(); // プライベートコンストラクタ
    static DeviceInOut* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    DeviceInOut(DeviceInOut const&);
    void operator=(DeviceInOut const&);
};

#endif  // DEVICE_IN_OUT_H