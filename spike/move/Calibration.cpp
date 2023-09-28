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
    if(std::strcmp(command, "record:brightness") == 0){
        this->state = true;
        this->recordType = 1;
    }else if(std::strcmp(command, "record:color") == 0){
        this->state = true;
        this->recordType = 2;
    }else if(std::strcmp(command, "stop") == 0){
        this->stop();
        this->state = false;
        this->recordType = 0;
    }else{
        printf("error : unknown command at calibration::first()\n");
    }
}

void Calibration::execute(){
    if(this->recordType == 1){
        this->device.color_getBrightness();
    }else{ //recordType == 2
        this->device.color_getRawColor();
    }
}

void Calibration::stop(){
    std::list<int> valueList;
    //レコードの取得
    for(int i = 0; i < this->record.getRecordLimit(); i++){
        bool isExist;
        SensorData sensorData = this->record.getSensorData(i);

        int value;
        if(this->recordType == 1){ // 反射光
            value = int(sensorData.getBrightness(isExist));
        }else{ //recordType = 2       カラーセンサ
            rgb_raw_t rgb = sensorData.getRGB(isExist);
            this->rgb2hsv.update(rgb);
            unit::hsv_t hsv = this->rgb2hsv.getHSV();
        }

        if(isExist == true){
            valueList.push_back(value);
            //printf("%d, ", value);
        }
    }

    //統計量の計算
    unit::calibration_t calibration = {-32767, 32767, 0};
    for (const auto& x : valueList) {
        if(calibration.max < x){
            calibration.max = x;
        }
        if(calibration.min > x){
            calibration.min = x;
        }
    }
    calibration.avg = int((calibration.max + calibration.min) / 2.0);
    //格納
    if(this->recordType == 1){ // 反射光
        printf("[Brightness] 平均:%d, 最大:%d, 最小:%d\n", calibration.avg, calibration.max, calibration.min);
        this->generalData.setBrightness(calibration);
    }else{ //recordType = 2       カラーセンサ
        printf("[Color] 平均:%d, 最大:%d, 最小:%d\n", calibration.avg, calibration.max, calibration.min);
        this->generalData.setColor(calibration);
    }
}

bool Calibration::getState(){
    return this->state;
}