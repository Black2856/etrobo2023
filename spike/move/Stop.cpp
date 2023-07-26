/*
クラス名:Stop
作成日:2023/07/21
作成者:船田
*/
#include "Stop.h"

Stop::Stop():
    device(DeviceInOut::getInstance()){
    }

void Stop::first(float pwmTransitionTime){
    this->calc.pwmCalc.setPWM(0, pwmTransitionTime);
}

bool Stop::execute(float pwmTransitionTime){ //pwmが0に達したらtrueを返す
    int correctionPWM = this->calc.pwmCalc.changePWM();
    
    this->device.LWheel_setPWM(correctionPWM);
    this->device.RWheel_setPWM(correctionPWM);

    if(correctionPWM == 0){
        return true;
    }else{
        return false;
    }
}