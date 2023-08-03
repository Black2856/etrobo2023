/*
クラス名:Calibration
作成日:2023/7/26
作成者:船田
*/
#include "Calibration.h"

Calibration::Calibration():
    device(DeviceInOut::getInstance()){
    }

void Calibration::first(const char* command){
    if(std::strcmp(command, "record") == 0){
        this->state = true;
    }else if(std::strcmp(command, "stop") == 0){
        this->stop();
        this->state = false;
    }else{
        printf("error : unknown command at calibration::first()\n");
    }
}

void Calibration::execute(){
    this->device.color_getBrightness();
}

void Calibration::stop(){
    std::list<int> brightnessList;
    //レコードの取得
    for(int i = 0; i < this->record.getRecordLimit(); i++){
        bool isExist;
        SensorData sensorData = this->record.getSensorData(i);
        int value = int(sensorData.getBrightness(isExist));
        if(isExist == true){
            brightnessList.push_back(value);
        }
    }

    //統計量の計算
    unit::calibration_t calibration = {-32767, 32767, 0};
    for (const auto& x : brightnessList) {
        if(calibration.max < x){
            calibration.max = x;
        }
        if(calibration.min > x){
            calibration.min = x;
        }
    }
    calibration.avg = int(calibration.max / calibration.min);
    //格納
    printf("平均 %d", calibration.avg);
    this->generalData.setCalibration(calibration);
}

bool Calibration::getState(){
    return this->state;
}