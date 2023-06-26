/*
 * クラス名:PIDControl
 * 作成日:2023/06/26
 * 作成者:松尾
 */
#include "PIDControl.h"
#include "setting.h"

PIDControl::PIDControl():
    mPID([0,0,0]),
    mCurrent(0),
    mTarget(0),
    mIntegral(0),
    mDiff_prev(0){}


void PIDControl::setPID(unit::pid_t pid){
    mPID = pid;
}

float PIDControl::calc(float current,float target){
    // 偏差を計算
    float diff = current - target;
    // 偏差の累積地を更新
    mIntegral += diff * CYCLE;
    // 前回偏差との差を計算
    float ddt = diff - mDiff_prev;
    // 前回偏差を更新
    mDiff_prev = diff;

    // 計算した操作量を返却
    return diff * mPID.p + mIntegral * mPID.i + ddt * mPID.d;
    
}