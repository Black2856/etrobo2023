/*
 * クラス名:JudgeTouch
 * 作成日:2023/07/21
 * 作成者:松尾
 */
#include "JudgeTouch.h"

JudgeTouch::JudgeTouch():
    device(DeviceInOut::getInstance()){
}

bool JudgeTouch::j(bool flag){
    return this->flag;
}

void JudgeTouch::setFlag(bool flag){
    this->flag=device.touch_isPressed();
}