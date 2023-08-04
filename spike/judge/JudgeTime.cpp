/*
 * クラス名:JudgeTime
 * 作成日:2023/05/19
 * 作成者:杉本
 */
#include "JudgeTime.h"

JudgeTime::JudgeTime():
    JudgeNumerical(),
    device(DeviceInOut::getInstance()){
}

float JudgeTime::getValue() const {
    
    return device.clock_now();
}