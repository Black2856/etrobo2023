/*
 * クラス名:SpeedCorrection
 * 作成日:2023/06/14
 * 作成者:杉本
 */
#ifndef SPEED_CORRECTION_H
#define SPEED_CORRECTION_H

#include "DeviceInOut.h"

enum class easing_t {
    IN_OUT_QUAD = 1
};

class SpeedCorrection {  // <1>
public:
    SpeedCorrection();

    void init(float initialValue, float targetValue, float duration, easing_t easing);
    float calc();

private:
    DeviceInOut& device;
    // 初期値
    float mInitialValue;
    // 目標値
    float mTargetValue;
    // 制御の継続時間
    int mDuration;
    // 制御開始時間
    int mInitialTime;
    // イージング関数種別
    easing_t mEasing;

    float easeInOutQuad(float x);

};

#endif  // SPEED_CORRECTION_H