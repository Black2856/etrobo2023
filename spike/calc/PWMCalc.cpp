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
    judgeNumerical_t judgeValue = this->judgeData.getMostReached();
    float ret = this->beforePWM;

    if(judgeValue.rate <= progThreshold){
        float rate = judgeValue.rate / progThreshold;
        ret = int(this->speedCorrectionIn.calc(rate + 0.001) + 0.5);
    }else if(judgeValue.rate >= (1 - progThreshold)){
        float rate = (judgeValue.rate - (1 - progThreshold)) / progThreshold;
        ret = int(this->speedCorrectionOut.calc(rate + 0.001) + 0.5);
    }

    return ret;
}

//progThresholdが+の場合 前pwm => pwm => 前pwm の変化
//progThresholdが-の場合 前pwm => pwm の変化
void PWMCalc::setPWM(int pwm, float progThreshold){
    //PWMの制限
    if((0 <= this->beforePWM) && (this->beforePWM < 40)){
        this->beforePWM = 40;
    }else if((-40 < this->beforePWM) && (this->beforePWM <= 0)){
        this->beforePWM = -40;
    }

    if(progThreshold >= 0){
        this->speedCorrectionOut.init(pwm, this->beforePWM, easing_t::IN_OUT_QUAD);
    }else{
        this->speedCorrectionOut.init(pwm, pwm, easing_t::IN_OUT_QUAD);
    }
        this->speedCorrectionIn.init(this->beforePWM, pwm, easing_t::IN_OUT_QUAD);
        this->progThreshold = std::abs(progThreshold);

    this->beforePWM = pwm;
}