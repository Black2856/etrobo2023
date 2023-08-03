/*
 * クラス名:Manual
 * 作成日:2023/07/24
 * 作成者:船田
 */

#include "Manual.h"

Manual::Manual():
    device(DeviceInOut::getInstance()){
    }

void Manual::setPWM(float pwm, float pwmTransitionTime){
    this->calc.pwmCalc.setPWM(pwm, pwmTransitionTime);
}

void Manual::first(RunType runType, float pwm, float pwmTransitionTime){
    this->runType = runType;
    this->setPWM(pwm, pwmTransitionTime);
    this->calc.localization.resetDifferenceCount();
    this->standardDirection = this->calc.localization.getDirection();
}

void Manual::execute(){
    switch(this->runType){
        case RunType::STRAIGHT:
            this->straight();
            break;
        case RunType::CENTER_ROTATION:
            this->centerRotation();
            break;
        case RunType::LEFT_WHEEL_ROTATION:
            this->wheelRotation(0);
            break;
        case RunType::RIGHT_WHEEL_ROTATION:
            this->wheelRotation(1);
            break;
    }
}

void Manual::straight(){
    int correctionPWM = this->calc.pwmCalc.changePWM();
    //直進移動になるように補正する
    //float differenceCount = calc.localization.getDifferenceCount();
    float differenceDirection = this->standardDirection - this->calc.localization.getDirection();
    int gain = int(std::sqrt(differenceDirection) * 2.5 + 0.5);
    this->device.LWheel_setPWM(correctionPWM + gain);
    this->device.RWheel_setPWM(correctionPWM - gain);
}

void Manual::centerRotation(){
    int correctionPWM = this->calc.pwmCalc.changePWM();

    this->device.LWheel_setPWM(correctionPWM);
    this->device.RWheel_setPWM(-correctionPWM);
}

void Manual::wheelRotation(int wheel){
    int correctionPWM = this->calc.pwmCalc.changePWM();

    if(wheel == 0){ //左車輪を中心に回転
        this->device.LWheel_setPWM(0);
        this->device.RWheel_setPWM(correctionPWM);
    }else if(wheel == 1){ //右車輪を中心に回転
        this->device.LWheel_setPWM(correctionPWM);
        this->device.RWheel_setPWM(0);
    }
}