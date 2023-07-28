/*
クラス名:LineTrace
作成日:2023/06/26
作成者:松尾
*/
#include "LineTrace.h"

LineTrace::LineTrace():
    device(DeviceInOut::getInstance()){
        this->calibration = {0, 0, 0};
    }

void LineTrace::setPWM(float pwm, float pwmTransitionTime){
    this->calc.pwmCalc.setPWM(pwm, pwmTransitionTime);
}

void LineTrace::first(float pwm, float kp, float ki, float kd, float pwmTransitionTime){
    this->setPWM(pwm, pwmTransitionTime);
    this->pidControl.setPID({kp, ki, kd});
    this->calibration = {10, 20, 15}; //記録パッケージからキャリブレーションを読み込む予定
}

void LineTrace::trace(){
    int correctionPWM = this->calc.pwmCalc.changePWM();
    //printf("%d\n", correctionPWM);
    float gain = this->pidControl.calc(device.color_getBrightness(), this->calibration.avg);

    this->device.LWheel_setPWM(correctionPWM - int(gain + 0.5));
    this->device.RWheel_setPWM(correctionPWM + int(gain + 0.5));
}