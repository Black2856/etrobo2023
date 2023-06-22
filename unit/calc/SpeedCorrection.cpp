/*
 * クラス名:SpeedCorrection
 * 作成日:2023/06/14
 * 作成者:杉本
 */
#include "SpeedCorrection.h"

SpeedCorrection::SpeedCorrection():
    device(DeviceInOut::getInstance()),
    mInitialValue(0),
    mTargetValue(0),
    mDuration(0),
    mInitialTime(0),
    mEasing(IN_OUT_QUAD)
    {}

// 各値の初期化
void SpeedCorrection::init(float initialValue, float targetValue, float duration, easing_t easing) {
    mInitialValue = initialValue;
    mTargetValue = targetValue;
    // secからusecに変換
    mDuration = static_cast<uint64_t>(1000 * 1000 * duration);
    mInitialTime = device.clock_now();
    mEasing = easing;
}

float SpeedCorrection::calc() {
    // 経過時間
    uint64_t elapsed = device.clock_now() - mInitialTime;
    if (elapsed >= mDuration) {
        return mTargetValue;
    }
    float progress = elapsed / mDuration;

    switch (mEasing) {
    case IN_OUT_QUAD:
        return easeInOutQuad(progress);
    default:
        return easeInOutQuad(progress);
    }

    ;
}


float SpeedCorrection::easeInOutQuad(float x) {
    if (x < 0.5) {
        return 2 * x * x;
    } else {
        float t = -2 * x + 2;
        return 1 - (t * t) / 2;
    }
}