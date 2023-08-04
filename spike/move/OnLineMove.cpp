/*
クラス名:OnLineMove
作成日:2023/7/26
作成者:船田
*/

#include "OnLineMove.h"

OnLineMove::OnLineMove():
    device(DeviceInOut::getInstance()){
        this->calibration = {0, 0, 0};
    }

void OnLineMove::first(int maxPWM, float kp, float ki, float kd){
    this->maxPWM = maxPWM;
    this->manual.first(RunType::CENTER_ROTATION, 0, 0);
    this->pidControl.setPID({kp, ki, kd});
    this->calibration = this->generalData.getCalibration();
}

bool OnLineMove::execute(){
    float operation = this->pidControl.calc(float(device.color_getBrightness()), this->calibration.avg);
    //PWMの制限
    if(operation > this->maxPWM){
        operation = this->maxPWM;
    }else if(operation < -this->maxPWM){
        operation = -this->maxPWM;
    }

    this->manual.setPWM(operation, 0);
    this->manual.execute();

    if((-10 <= operation) and (operation <= 10)){
        return true;
    }
    return false;
}