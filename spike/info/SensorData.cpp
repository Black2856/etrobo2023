/*
 * クラス名:SensorData
 * 作成日:2023/08/02
 * 作成者:船田
 */
#include "SensorData.h"

// get関数群 //
int32_t         SensorData::getLeftWheelCount(bool& isExist){
    isExist = this->checkExist(0);
    return this->left_wheel_count;
}
int32_t     SensorData::getRightWheelCount(bool& isExist){
    isExist = this->checkExist(1);
    return this->right_wheel_count;
}
int16_t     SensorData::getSonarDistance(bool& isExist){
    isExist = this->checkExist(2);
    return this->sonar_distance;
}
bool        SensorData::getTouchPressed(bool& isExist){
    isExist = this->checkExist(3);
    return this->touch_pressed;
}
int16_t     SensorData::getGyroAngle(bool& isExist){
    isExist = this->checkExist(4);
    return this->gyro_angle;
}
int16_t     SensorData::getBrightness(bool& isExist){
    isExist = this->checkExist(5);
    return this->brightness;
}
rgb_raw_t   SensorData::getRGB(bool& isExist){
    isExist = this->checkExist(6);
    return this->rgb;
}
uint64_t    SensorData::getClockTime(bool& isExist){
    isExist = this->checkExist(7);
    return this->clock_time;
}
int         SensorData::getBatteryCurrent(bool& isExist){
    isExist = this->checkExist(8);
    return this->battery_current;
}
int         SensorData::getBatteryVoltage(bool& isExist){
    isExist = this->checkExist(9);
    return this->battery_voltage;
}
// set関数群 //
void        SensorData::setLeftWheelCount(int32_t value){
    this->addExist(0);
    this->left_wheel_count = value;
}
void        SensorData::setRightWheelCount(int32_t value){
    this->addExist(1);
    this->right_wheel_count = value;
}
void        SensorData::setSonarDistance(int16_t value){
    this->addExist(2);
    this->sonar_distance = value;
}
void        SensorData::setTouchPressed(bool value){
    this->addExist(3);
    this->touch_pressed = value;
}
void        SensorData::setGyroAngle(int16_t value){
    this->addExist(4);
    this->gyro_angle = value;
}
void        SensorData::setBrightness(int16_t value){
    this->addExist(5);
    this->brightness = value;
}
void        SensorData::setRGB(rgb_raw_t value){
    this->addExist(6);
    this->rgb = value;
}
void        SensorData::setClockTime(uint64_t value){
    this->addExist(7);
    this->clock_time = value;
}
void        SensorData::setBatteryCurrent(int value){
    this->addExist(8);
    this->battery_current = value;
}
void        SensorData::setBatteryVoltage(int value){
    this->addExist(9);
    this->battery_voltage = value;
}
// exist関数群 //
bool        SensorData::checkExist(int bit){
    int mask = ~(1 << bit);
    int maskBit = this->dataMask | mask;
    //std::bitset<データ数>(maskBit) == 0bデータ数分のビット「1」
    bool isExist = (std::bitset<10>(maskBit) == 0b1111111111);
    return isExist;
}
void        SensorData::addExist(int bit){
    int mask = 1 << bit;
    this->dataMask = this->dataMask | mask; 
}