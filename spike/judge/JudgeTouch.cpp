/*
 * クラス名:JudgeTouch
 * 作成日:2023/07/21
 * 作成者:松尾
 */
#include "JudgeTouch.h"

JudgeTouch::JudgeTouch():
    device(DeviceInOut::getInstance()){
}

float JudgeTouch::getValue() const {
    return device.touch_isPressed();
}