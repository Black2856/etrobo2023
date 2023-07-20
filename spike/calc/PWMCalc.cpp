/*
クラス名:PWMCalc
作成日:2023/07/19
作成者:船田
*/

#include "PWMCalc.h"

PWMCalc::PWMCalc(){
    this->beforePWM = 0;
}

int PWMCalc::changePWM(){
    return int(this->speedCorrection.calc() + 0.5);
}

void PWMCalc::setPWM(int pwm, float time){
    this->speedCorrection.init(this->beforePWM, pwm, time, easing_t::IN_OUT_QUAD);

    this->beforePWM = pwm;
}