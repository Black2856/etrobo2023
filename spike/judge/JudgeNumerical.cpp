/*
 * クラス名:JudgeNumerical
 * 作成日:2023/05/19
 * 作成者:杉本
 */
#include "JudgeNumerical.h"
#include <math.h>

JudgeNumerical::JudgeNumerical():
    mTarget(0),
    mStartNumerical(0),
    mStartFlg(false) {
}

bool JudgeNumerical::j(float target) {
    // 間隔がセットされていない場合
    if (!isStarted()) {
        setTarget(target);
        start();
    }
    // 目標値に達した場合
    if (isTargetReached()) {
        //stop();
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
    mStartNumerical = getValue();
    mStartFlg = true;
}

/**
 * 計測停止
 */
void JudgeNumerical::stop() {
    this->previousValue = 0;
    mStartNumerical = 0;
    mStartFlg = false;
}

/**
 * 目標値に達したか否か
 * @retval true  目標値に達した
 * @retval false 目標値に達していない
 */
bool JudgeNumerical::isTargetReached(){
    float currentNumerical = getValue() - mStartNumerical;
    this->previousValue = currentNumerical;
    if(mTarget >= 0){
        return (currentNumerical >= mTarget) ? true : false;
    }else{ //mTarget < 0
        return (currentNumerical < mTarget) ? true : false;
    }
}

/**
 * 計測開始したか否か
 * @retval true  計測開始した
 * @retval false 計測開始していない
 */
bool JudgeNumerical::isStarted() const {
    return mStartFlg;
}

float JudgeNumerical::getPreviousValue() const {
    return this->previousValue;
}

float JudgeNumerical::getTarget() const {
    return mTarget;
}

float JudgeNumerical::getStartNumerical() const {
    return mStartNumerical;
}