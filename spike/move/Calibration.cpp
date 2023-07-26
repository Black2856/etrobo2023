/*
クラス名:Calibration
作成日:2023/7/26
作成者:船田
*/
#include "Calibration.h"

Calibration::Calibration():
    device(DeviceInOut::getInstance()){
        }


bool Calibration::execute(float pwm){
    return false;
}

void Calibration::getFase(){

}

void Calibration::onLineFase(){

}