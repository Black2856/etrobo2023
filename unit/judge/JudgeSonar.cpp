/*
 * クラス名:JudgeSonar
 * 作成日：2023/05/19
 * 作成者:杉本
 */
#include "JudgeSonar.h"

JudgeSonar::JudgeSonar():
    JudgeNumerical(),
    device(DeviceInOut::getInstance()){
}

float JudgeSonar::getValue() const {
    return device.sonar_getDistance();
}

bool  JudgeAngle::isTargetReached() const {
    // 計測開始時より近い距離が目標の場合
    if (mStartNumerical > mTarget) {
        return (getValue() <= mTarget) ? true : false;
    } else {
        return (getValue() >= mTarget) ? true : false;
    }
}