/*
 * クラス名:JudgeButton
 * 作成日:2023/08/25
 * 作成者:船田
 */
#include "JudgeButton.h"

JudgeButton::JudgeButton():
    device(DeviceInOut::getInstance()){
}

// LEFT_BUTTON  = 0
// RIGHT_BUTTON = 1
// ENTER_BUTTON = 4
bool JudgeButton::j(int button, bool flag){
    return this->device.button_isPressed(button_t(button)) == flag;
}