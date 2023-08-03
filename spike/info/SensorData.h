/*
 * クラス名:SensorData
 * 作成日:2023/08/02
 * 作成者:船田
 */
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "ev3api.h"
#include "unit.h"
#include <bitset>

class SensorData {
public:
    //返り値に値、引数の参照返り値はデータが存在するかを返す
    int32_t     getLeftWheelCount(bool& isExist);
    int32_t     getRightWheelCount(bool& isExist);
    int16_t     getSonarDistance(bool& isExist);
    bool        getTouchPressed(bool& isExist);
    int16_t     getGyroAngle(bool& isExist);
    int16_t     getBrightness(bool& isExist);
    rgb_raw_t   getRGB(bool& isExist);
    uint64_t    getClockTime(bool& isExist);
    int         getBatteryCurrent(bool& isExist);
    int         getBatteryVoltage(bool& isExist);

    void        setLeftWheelCount(int32_t value);
    void        setRightWheelCount(int32_t value);
    void        setSonarDistance(int16_t value);
    void        setTouchPressed(bool value);
    void        setGyroAngle(int16_t value);
    void        setBrightness(int16_t value);
    void        setRGB(rgb_raw_t value);
    void        setClockTime(uint64_t value);
    void        setBatteryCurrent(int value);
    void        setBatteryVoltage(int value);

private:
    bool        checkExist(int bit); //データが存在するかチェック
    void        addExist(int bit); //データを存在を変更する

    int         dataMask = 0b0000000000;//下記内容データが存在するかのビット列
    int32_t     left_wheel_count;       //0
    int32_t     right_wheel_count;      //1
    int16_t     sonar_distance;         //2
    bool        touch_pressed;          //3
    int16_t     gyro_angle;             //4
    int16_t     brightness;             //5
    rgb_raw_t   rgb;                    //6
    uint64_t    clock_time;             //7
    int         battery_current;        //8
    int         battery_voltage;        //9
};

#endif

