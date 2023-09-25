/*
 * クラス名:GeneralData
 * 作成日:2023/08/02
 * 作成者:船田
 */
#include "GeneralData.h"

GeneralData* GeneralData::instance = NULL;

GeneralData::GeneralData(){

}

GeneralData& GeneralData::getInstance() {
    if (!instance) {
        instance = new GeneralData();
    }
    return *instance;
}

unit::calibration_t GeneralData::getBrightness(){
    return this->brightness;
}

void GeneralData::setBrightness(unit::calibration_t brightness){
    this->brightness = brightness;
}

unit::calibration_t GeneralData::getColor(){
    return this->color;
}

void GeneralData::setColor(unit::calibration_t color){
    this->color = color;
}

bool GeneralData::getFlag(int idx){
    return this->flag[idx];
}
void GeneralData::setFlag(int idx, bool flag){
    this->flag[idx] = flag;
}

int GeneralData::getMinifigDegree(){
    return this->minifigDegree;
}
void GeneralData::setMinifigDegree(int degree){
    this->minifigDegree = degree;
}