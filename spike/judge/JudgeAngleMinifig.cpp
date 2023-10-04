/*
 * クラス名:JudgeAngleMinifig
 * 作成日:2023/09/29
 * 作成者:船田
 */
#include "JudgeAngleMinifig.h"

JudgeAngleMinifig::JudgeAngleMinifig():
    JudgeNumerical(),
    device(DeviceInOut::getInstance()),
    localization(Localization::getInstance()){
}

float JudgeAngleMinifig::getValue() const {
    //return device.gyro_getAngle();
    return this->localization.getDirection() * FRICTIONAL;
}

float JudgeAngleMinifig::targetConvert(float target) const {
    float t = float(this->generalData.getMinifigDegree());
    if(target == 1){
        return t;
    }else if(target == 2){
        return (360 - t);
    }else if(target == -1){
        return -t;
    }else if(target == -2){
        return -(360 - t);
    }else{
        printf("JudgeAngleMinifig : wrong target (1,2,-1,-2)");
    }
}