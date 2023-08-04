/*
 * クラス名:JudgeData
 * 作成日:2023/08/04
 * 作成者:船田
 */

#include "JudgeData.h"

JudgeData* JudgeData::instance = NULL;

JudgeData::JudgeData(){

}

JudgeData& JudgeData::getInstance() {
    if (!instance) {
        instance = new JudgeData();
    }
    return *instance;
}

judgeValue_t JudgeData::getJudgeValue(){
    judgeValue_t init;
    this->judgeValue = init;
    this->judgeValue.angle.isStarted = j.angle.getTarget();
    if(this->judgeValue.angle.isStarted == true){
        this->judgeValue.angle.now = j.angle.getPreviousValue();
        this->judgeValue.angle.target = j.angle.getTarget();
        this->judgeValue.angle.rate = this->judgeValue.angle.now / this->judgeValue.angle.target;
    }
    this->judgeValue.mileage.isStarted = j.mileage.getTarget();
    if(this->judgeValue.mileage.isStarted == true){
        this->judgeValue.mileage.now = j.mileage.getPreviousValue();
        this->judgeValue.mileage.target = j.mileage.getTarget();
        this->judgeValue.mileage.rate = this->judgeValue.mileage.now / this->judgeValue.mileage.target;
    }
    this->judgeValue.sonar.isStarted = j.sonar.getTarget();
    if(this->judgeValue.sonar.isStarted == true){
        this->judgeValue.sonar.now = j.sonar.getPreviousValue();
        this->judgeValue.sonar.target = j.sonar.getTarget();
        this->judgeValue.sonar.rate = this->judgeValue.sonar.now / this->judgeValue.sonar.target;
    }
    this->judgeValue.time.isStarted = j.time.getTarget();
    if(this->judgeValue.time.isStarted == true){
        this->judgeValue.time.now = j.time.getPreviousValue();
        this->judgeValue.time.target = j.time.getTarget();
        this->judgeValue.time.rate = this->judgeValue.time.now / this->judgeValue.time.target;
    }
    return this->judgeValue;
}

judgeNumerical_t JudgeData::getMostReached(){
    judgeNumerical_t ret;
    this->getJudgeValue();

    float rateList[] = {
        this->judgeValue.angle.rate,
        this->judgeValue.mileage.rate,
        this->judgeValue.sonar.rate,
        this->judgeValue.time.rate
    };

    int targetIdx = 0;
    for(int i = 1; i < int(sizeof(rateList) / sizeof(float)); i++){
        if(rateList[i] > rateList[targetIdx]){
            targetIdx = i;
        }
    }

    switch(targetIdx){
        case 0:
            ret = this->judgeValue.angle;
            break;
        case 1:
            ret = this->judgeValue.mileage;
            break;
        case 2:
            ret = this->judgeValue.sonar;
            break;
        case 3:
            ret = this->judgeValue.time;
            break;
    }

    return ret;
}