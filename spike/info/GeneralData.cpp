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

unit::calibration_t GeneralData::getCalibration(){
    return this->calibration;
}

void GeneralData::setCalibration(unit::calibration_t calibration){
    this->calibration = calibration;
}