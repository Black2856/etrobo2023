/*
 * クラス名:Manual
 * 作成日:2023/07/24
 * 作成者:船田
 */

#include "Manual.h"

Manual::Manual():
    device(DeviceInOut::getInstance()){
        unit::pid_t pid1 = {0.2, 0, 0.4};
        //1.25, 0.025, 0.6
        //0.2, 0.001, 0.15
        this->straightPID.setPID(pid1);
        unit::pid_t pid2 = {2.3, 0.022, 0.15};
        this->centerPID.setPID(pid2);
    }

void Manual::setPWM(float pwm, float pwmTransitionTime){
    this->calc.pwmCalc.setPWM(pwm, pwmTransitionTime); 
}

void Manual::first(manual::RunType runType, float pwm, float pwmTransitionTime){
    this->straightPID.resetPID();
    this->centerPID.resetPID();
    this->maeDistance = 0;
    this->Xmove = 0;

    this->runType = runType;
    this->setPWM(pwm, pwmTransitionTime);
    this->calc.localization.resetDifferenceCount();
    this->standardDirection = this->calc.localization.getDirection();
    this->standardDistance = this->calc.localization.getDistance();
}

void Manual::execute(){
    switch(this->runType){
        case manual::RunType::STRAIGHT:
            this->straight();
            break;
        case manual::RunType::CENTER_ROTATION:
            this->centerRotation();
            break;
        case manual::RunType::LEFT_WHEEL_ROTATION:
            this->wheelRotation(0);
            break;
        case manual::RunType::RIGHT_WHEEL_ROTATION:
            this->wheelRotation(1);
            break;
        default:
            printf("error : incorrect type at Manual::execute");
            break;
    }
}

void Manual::straight(){
    int correctionPWM = this->calc.pwmCalc.changePWM();
    //直進移動になるように補正する
    float differenceDirection = this->standardDirection - this->calc.localization.getDirection();

    float deltaDistance = this->calc.localization.getDistance() - this->maeDistance;
    this->maeDistance = this->calc.localization.getDistance();
    float deltaXmove = deltaDistance * std::sin(PI / 180 * differenceDirection);
    this->Xmove += deltaXmove;

    this->fix += this->straightPID.calc(this->Xmove, 0);
    //int gain = int(differenceDirection * 2.3 + 0.5);

    int gain = int(fix);
    printf("%f, ",this->Xmove);

    this->device.LWheel_setPWM(correctionPWM + gain);
    this->device.RWheel_setPWM(correctionPWM - gain);

    this->fix = this->fix - gain;
}

void Manual::centerRotation(){
    int correctionPWM = this->calc.pwmCalc.changePWM();
    //車体中心移動になるように補正する
    float differenceDistance = this->standardDistance - this->calc.localization.getDistance();
    int gain = int(this->centerPID.calc(differenceDistance, 0));
    //printf("%d", gain);

    this->device.LWheel_setPWM(correctionPWM + gain);
    this->device.RWheel_setPWM(-(correctionPWM - gain));
}

void Manual::wheelRotation(int wheel){
    int correctionPWM = this->calc.pwmCalc.changePWM();

    if(wheel == 0){ //左車輪を中心に回転
        this->device.LWheel_setPWM(0);
        this->device.RWheel_setPWM(correctionPWM);
    }else if(wheel == 1){ //右車輪を中心に回転
        this->device.LWheel_setPWM(correctionPWM);
        this->device.RWheel_setPWM(0);
    }else{
        printf("error : incorrect type at Manual::wheelRotation");
    }
}