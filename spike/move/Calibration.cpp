/*
クラス名:Calibration
作成日:2023/7/26
作成者:船田
*/
#include "Calibration.h"

Calibration::Calibration(){}

void Calibration::first(const char* command){
    if(strcmp(command, "record")){
        this->state = true;
    }else if(strcmp(command, "stop")){
        this->stop();
        this->state = false;
    }
}

void Calibration::record(){
    printf("record \n");
}

void Calibration::stop(){
}

bool Calibration::getState(){
    return this->state;
}