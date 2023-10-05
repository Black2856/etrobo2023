/*
 * クラス名:JudgeBrightness
 * 作成日:2023/09/29
 * 作成者:船田
 */
#include "JudgeBrightness.h"

JudgeBrightness::JudgeBrightness():
    JudgeNumerical(),
    device(DeviceInOut::getInstance()){}

float JudgeBrightness::getValue() const {
    // printf("%d, ", this->device.color_getBrightness());
    return this->device.color_getBrightness();
}

bool  JudgeBrightness::isTargetReached() const {
    // 計測開始時より近い距離が目標の場合
    if (getStartNumerical() > getTarget()) {
        return (getValue() <= getTarget()) ? true : false;
    } else {
        return (getValue() >= getTarget()) ? true : false;
    }
}