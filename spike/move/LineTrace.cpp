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

void LineTrace::first(int pwm, float kp, float ki, float kd){
    this->calc.pwmCalc.setPWM(pwm, 0.5);
    this->pidControl.setPID({kp, ki, kd});
    this->calibration = {10, 20, 15}; //記録パッケージからキャリブレーションを読み込む予定
}

void LineTrace::trace(int pwm, float kp, float ki, float kd){
    int correctionPWM = calc.pwmCalc.changePWM();
    //printf("%d\n", correctionPWM);
    float gain = pidControl.calc(device.color_getBrightness(), calibration.avg);

    device.LWheel_setPWM(correctionPWM - int(gain + 0.5));
    device.RWheel_setPWM(correctionPWM + int(gain + 0.5));
}