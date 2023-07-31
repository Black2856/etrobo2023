/*
 * クラス名:JudgeAngle
 * 作成日:2023/05/19
 * 作成者:杉本
 */
#include "JudgeAngle.h"

JudgeAngle::JudgeAngle():
    JudgeNumerical(),
    device(DeviceInOut::getInstance()),
    localization(Localization::getInstance()){
}

float JudgeAngle::getValue() const {
    //return device.gyro_getAngle();
    return this->localization.getDirection();
}