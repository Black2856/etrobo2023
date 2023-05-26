/*
 * クラス名:JudgeTime
 * 作成日：2023/05/19
 * 作成者:杉本
 */
#include "JudgeTime.h"

JudgeTime::JudgeTime():
    device(DeviceInOut::getInstance()),
    mDelayMs(0),
    mStartTime(0),
    mTargetTime(0) {
}

bool JudgeTime::judge(uint32_t delay) {
    // タイマがセットされていない場合
    if (!isStarted()) {
        setTime(delay);
        start();
    }
    // タイマ満期した場合
    if (isTimedOut()) {
        stop();
        return true;
    }
    return false;
}

/**
 * タイマ満期時間設定
 * @param delay 満期時間[us]
 */
void JudgeTime::setTime(uint32_t delay) {
    mDelayMs = delay;
}

/**
 * タイマ開始
 */
void JudgeTime::start() {
    mStartTime  = device.clock_now();
    mTargetTime = mStartTime + mDelayMs;
}

/**
 * タイマ停止
 */
void JudgeTime::stop() {
    mStartTime  = 0;
    mTargetTime = 0;
}

/**
 * タイマ満期したか否か
 * @retval true  タイマ満期した
 * @retval false タイマ満期していない
 */
bool JudgeTime::isTimedOut() const {
    return (device.clock_now() >= mTargetTime) ? true : false;
}

/**
 * タイマ開始したか否か
 * @retval true  タイマ開始した
 * @retval false タイマ開始していない
 */
bool JudgeTime::isStarted() const {
    return (mStartTime == 0) ? false : true;
}
