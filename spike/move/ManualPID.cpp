/*
クラス名:ManualPID
作成日:2023/7/26
作成者:船田
*/

#include "ManualPID.h"

ManualPID::ManualPID():
    device(DeviceInOut::getInstance()){
        this->calibration = {0, 0, 0};
    }

//transitionValue : 遷移条件値
void ManualPID::first(manualPID::RunType runType, float maxPWM, float transitionValue){
    this->runType = runType;
    this->maxPWM = std::abs(maxPWM);
    this->rotation = rotation;
    this->pidControl.setPID({4.5, 0.001, 1.5});
    this->calibration = this->generalData.getCalibration();

    this->transitionValue = transitionValue;
    this->standardDistance = calc.localization.getDistance();
    this->standardDirection = calc.localization.getDirection();

    //マニュアルPIDに応じたマニュアルの動作指定
    manual::RunType manualType = manual::RunType::STRAIGHT;
    switch (runType){
    case manualPID::RunType::STRAIGHT:
        manualType = manual::RunType::STRAIGHT;
        break;
    case manualPID::RunType::CENTER_ROTATION:
        manualType = manual::RunType::CENTER_ROTATION;
        break;
    case manualPID::RunType::LEFT_WHEEL_ROTATION:
        manualType = manual::RunType::LEFT_WHEEL_ROTATION;
        break;
    case manualPID::RunType::RIGHT_WHEEL_ROTATION:
        manualType = manual::RunType::RIGHT_WHEEL_ROTATION;
        break;
    case manualPID::RunType::ON_LINE_MOVE:
        manualType = manual::RunType::CENTER_ROTATION;
        break;
    default:
        printf("error : incorrect type at ManualPID::first");
        break;
    }

    this->manual.first(manualType, 0, 0);
}

bool ManualPID::execute(){
    float operation = 0;
    
    switch (this->runType){
    case manualPID::RunType::STRAIGHT:
        operation = this->distance();
        break;
    case manualPID::RunType::CENTER_ROTATION:
        operation = this->direction();
        break;
    case manualPID::RunType::LEFT_WHEEL_ROTATION:
        operation = this->direction();
        break;
    case manualPID::RunType::RIGHT_WHEEL_ROTATION:
        operation = this->direction();
        break;
    case manualPID::RunType::ON_LINE_MOVE:
        operation = this->onLineMove();
        break;
    default:
        printf("error : incorrect type at ManualPID::execute");
        break;
    }
    
    //操作
    operation = this->max(operation, this->maxPWM);

    this->manual.setPWM(operation, 0);
    this->manual.execute();

    if((-30 <= operation) and (operation <= 30)){
        return true;
    }
    return false;
}

    //遷移条件値:走行距離(mileage)
    float ManualPID::distance(){
        float diffDistance = this->standardDistance - calc.localization.getDistance();
        return this->pidControl.calc(diffDistance, -this->transitionValue);
    }
    
    //遷移条件値:車体角度(angle)
    float ManualPID::direction(){
        float diffDirection = this->standardDirection - calc.localization.getDirection();
        return this->pidControl.calc(diffDirection, this->transitionValue);
    }
    //遷移条件値:無し
    float ManualPID::onLineMove(){
        return this->pidControl.calc(float(device.color_getBrightness()), this->calibration.avg);
    }

    float ManualPID::max(float value, float max){
        if(value > max){
            return max;
        }else if(value < -max){
            return -max;
        }else{
            return value;
        }
    }