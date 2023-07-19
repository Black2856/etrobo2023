/*
クラス名:PWMCalc
作成日:2023/07/19
作成者:船田
*/

#include "PWMCalc.h"

PWMCalc::PWMCalc(){
    this->nowPWM = 0;
    this->beforePWM = 0;
    this->duration = 0.5;
}

int PWMCalc::changePWM(){
    return this->speedCorrection.calc();
}

void PWMCalc::setPWM(int pwm, float time){
    this->beforePWM = this->nowPWM;
    this->nowPWM = pwm;
    this->changeTime = time;

    this->speedCorrection.init(pwm, this->nowPWM, this->duration);
}