/*
 * クラス名:JudgeNumerical
 * 作成日：2023/05/19
 * 作成者:杉本
 */
#include "JudgeNumerical.h"
#include <math.h>

JudgeNumerical::JudgeNumerical():
    mTarget(0),
    mStartNumerical(0) {
}

bool JudgeNumerical::judge(float target) {
    // 間隔がセットされていない場合
    if (!isStarted()) {
        setTarget(target);
        start();
    }
    // 目標値に達した場合
    if (isTargetReached()) {
        stop();
        return true;
    }
    return false;
}

/**
 * 間隔設定
 * @param target 間隔
 */
void JudgeNumerical::setTarget(float target) {
    mTarget = target;
}

/**
 * 計測開始
 */
void JudgeNumerical::start() {
    mStartNumerical  = getValue();
}


/**
 * 計測停止
 */
void JudgeNumerical::stop() {
    mStartNumerical  = 0;
}

/**
 * 目標値に達したか否か
 * @retval true  目標値に達した
 * @retval false 目標値に達していない
 */
bool JudgeNumerical::isTargetReached() const {
    float currentNumerical = getValue() - mStartNumerical;
    return (fabsf(currentNumerical) >= mTarget) ? true : false;
}


/**
 * 計測開始したか否か
 * @retval true  計測開始した
 * @retval false 計測開始していない
 */
bool JudgeNumerical::isStarted() const {
    return (mStartNumerical == 0) ? false : true;
}
