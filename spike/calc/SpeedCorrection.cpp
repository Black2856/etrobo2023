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
    mEasing(easing_t::IN_OUT_QUAD)
    {}

// 各値の初期化
void SpeedCorrection::init(float initialValue, float targetValue, float duration, easing_t easing) {
    mInitialValue = initialValue;
    mTargetValue = targetValue;
    // secからusecに変換
    mDuration = int(duration * 1000);
    mInitialTime = int(device.clock_now() / 1000);
    mEasing = easing;
}

float SpeedCorrection::calc() {
    // 経過時間
    int elapsed = int(device.clock_now() / 1000 - mInitialTime);
    if (elapsed >= mDuration) {
        return mTargetValue;
    }
    float progress = float(elapsed) / float(mDuration);

    switch (mEasing) {
        case easing_t::IN_OUT_QUAD:
            return mInitialValue + easeInOutQuad(progress) * (mTargetValue - mInitialValue);
        default:
            return mInitialValue + easeInOutQuad(progress) * (mTargetValue - mInitialValue);
    };
}

float SpeedCorrection::easeInOutQuad(float x) {
    float ret;
    if (x < 0.5) {
        ret = 2 * x * x;
    } else {
        float t = -2.0 * x + 2.0;
        ret = 1.0 - (t * t) / 2.0;
    }
    return ret;
}