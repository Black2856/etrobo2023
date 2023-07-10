/*
クラス名:LineTrace
作成日:2023/06/26
作成者:松尾
*/
#include "LineTrace.h"

LineTrace::LineTrace():
    device(DeviceInOut::getInstance()){
        this->cal = {0, 0, 0};
    }

void LineTrace::Trace(int pwm, float kp, float ki, float kd){
    this->cal = {10, 20, 15}; //記録パッケージからキャリブレーションを読み込む予定
    this->pidControl.setPID({kp, ki, kd});

    float gain = pidControl.calc(device.color_getBrightness(), cal.avg);
    device.LWheel_setPWM(pwm - gain);
    device.RWheel_setPWM(pwm + gain);
}