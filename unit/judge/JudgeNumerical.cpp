/*
 * クラス名:JudgeNumerical
 * 作成日：2023/05/19
 * 作成者:杉本
 */
#include "JudgeNumerical.h"

JudgeNumerical::JudgeNumerical():
    mInterval(0),
    mStartNumerical(0),
    mTargetNumerical(0) {
}

bool JudgeNumerical::judge(float interval) {
    // 間隔がセットされていない場合
    if (!isStarted()) {
        setInterval(interval);
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
 * @param interval 間隔
 */
void JudgeNumerical::setInterval(float interval) {
    mInterval = interval;
}

/**
 * 計測開始
 */
void JudgeNumerical::start() {
    mStartNumerical  = getValue();
    mTargetNumerical = mStartNumerical + mInterval;
}


/**
 * 計測停止
 */
void JudgeNumerical::stop() {
    mStartNumerical  = 0;
    mTargetNumerical = 0;
}

/**
 * 目標値に達したか否か
 * @retval true  目標値に達した
 * @retval false 目標値に達していない
 */
bool JudgeNumerical::isTargetReached() const {
    return (getValue() >= mTargetNumerical) ? true : false;
}


/**
 * 計測開始したか否か
 * @retval true  計測開始した
 * @retval false 計測開始していない
 */
bool JudgeNumerical::isStarted() const {
    return (mStartNumerical == 0) ? false : true;
}
