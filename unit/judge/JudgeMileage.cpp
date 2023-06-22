/*
 * クラス名:JudgeTime
 * 作成日:2023/05/28
 * 作成者:杉本
 */
#include "JudgeMileage.h"

JudgeMileage::JudgeMileage():
    JudgeNumerical(),
    localization(Localization::getInstance()){
}

float JudgeMileage::getValue() const {
    return localization.getDistance();
}