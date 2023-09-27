/*
クラス名:LineTrace
作成日:2023/06/26
作成者:松尾
*/
#include "LineTrace.h"

LineTrace::LineTrace():
    device(DeviceInOut::getInstance()){
        this->brightness = {0, 0, 0};
        this->color = {0, 0, 0};
    }

void LineTrace::setPWM(float pwm, float pwmTransitionTime){
    this->calc.pwmCalc.setPWM(pwm, pwmTransitionTime);
}

void LineTrace::first(float pwm, float kp, float ki, float kd, float pwmTransitionTime){
    this->setPWM(pwm, pwmTransitionTime);
    this->pidControl.setPID({kp, ki, kd});
    this->brightness = this->generalData.getBrightness();
    this->color = this->generalData.getColor();
}

void LineTrace::trace(){
    int correctionPWM = this->calc.pwmCalc.changePWM();
    //printf("%d\n", correctionPWM);

    // カラーセンサが前回で取得されている場合はカラーセンサでトレースをする
    /*
    bool isExist = false;
    SensorData sensorData = this->record.getSensorData(0);
    rgb_raw_t rgb1 = sensorData.getRGB(isExist);
    
    float gain;
    if(isExist == true){ //カラーセンサ
        this->rgb2hsv.update();
        unit::hsv_t hsv = this->rgb2hsv.getHSV();
        gain = this->pidControl.calc(float(hsv.v), this->color.avg);
    }else{ //反射光
        gain = this->pidControl.calc(float(device.color_getBrightness()), this->brightness.avg);
    }
    */

    // カラーセンサのみでトレース
    this->rgb2hsv.update();
    unit::hsv_t hsv = this->rgb2hsv.getHSV();
    gain = this->pidControl.calc(float(hsv.v), this->color.avg);

    this->device.LWheel_setPWM(correctionPWM - int(gain + 0.5));
    this->device.RWheel_setPWM(correctionPWM + int(gain + 0.5));  
}