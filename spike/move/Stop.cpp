/*
クラス名:Stop
作成日:2023/07/21
作成者:船田
*/
#include "Stop.h"

Stop::Stop():
    device(DeviceInOut::getInstance()){
    }

void Stop::first(){
    this->device.LWheel_setPWM(0);
    this->device.RWheel_setPWM(0);
}