/*
 * クラス名:Record
 * 作成日:2023/08/02
 * 作成者:船田
 */
#include "Record.h"

Record* Record::instance = NULL;

Record::Record(){
    this->recordLimit = RECORD_LIMIT; //センサー記録上限 記録秒数 = タスク間隔(ms) * recordLimit
    this->initRecordList();
}

Record& Record::getInstance() {
    if (!instance) {
        instance = new Record();
    }
    return *instance;
}

SensorData Record::getSensorData(int idx){
    return unit::getList(this->sensorList, idx);
}

int Record::getRecordLimit(){
    return this->recordLimit;
}

void Record::appendSensorData(){
    this->sensorList.push_back(sensorData);
    SensorData emptyData;
    this->sensorData = emptyData;
    if(int(this->sensorList.size()) > this->recordLimit){
        this->sensorList.pop_back();
    }
}

void Record::initRecordList(){
    this->sensorList.clear();
    
    SensorData emptyData;
    this->sensorData = emptyData;
    for(int i = 0; i < this->recordLimit; i++){
        this->appendSensorData();
    }
}