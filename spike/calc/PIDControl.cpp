/*
クラス名:PIDControl
作成日:2023/06/26
作成者:松尾
*/
#include "PIDControl.h"

PIDControl::PIDControl():
    mPID({0,0,0}),
    mCurrent(0),
    mTarget(0),
    mIntegral(0),
    mDiff_prev(0){}


void PIDControl::setPID(unit::pid_t pid){
    mPID = pid;
    this->resetPID();
}

void PIDControl::resetPID(){
    mIntegral = 0;
    mDiff_prev = 0;
}

float PIDControl::calc(float current,float target){
    // 偏差を計算 p
    float diff = current - target;
    // 偏差の累積地を更新 i
    mIntegral += diff * this->dt;
    
    // 前回偏差との差を計算と更新 d
    float ddt = (diff - mDiff_prev) / this->dt;
    mDiff_prev = diff;

    // 計算した操作量を返却
    return diff * mPID.kp + mIntegral * mPID.ki + ddt * mPID.kd;
}