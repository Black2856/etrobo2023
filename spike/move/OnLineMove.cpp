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

void OnLineMove::first(float kp, float ki, float kd){
    this->manual.first(RunType::CENTER_ROTATION, 0, 0);
    this->pidControl.setPID({kp, ki, kd});
    this->calibration = this->generalData.getCalibration(); //記録パッケージからキャリブレーションを読み込む予定
}

bool OnLineMove::execute(float gain){
    float operation = this->pidControl.calc(float(device.color_getBrightness()), this->calibration.avg) * gain;
    //PWMの制限
    /*
    if(operation > 100){
        operation = 100;
    }else if(operation < -100){
        operation = -100;
    }
    */

    this->manual.setPWM(operation, 0);
    this->manual.execute();

    if((-10 <= operation) and (operation <= 10)){
        return true;
    }
    return false;
}