/*
 * クラス名:PIDControl
 * 作成日:2023/06/26
 * 作成者:松尾
 */
#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include "unit.h"

class PIDControl {
public:
    PIDControl();//pid
    float calc(float current, float target);
    void setPID(unit::pid_t pid);
private:
    unit::pid_t mPID;
    float mCurrent;
    float mTarget;
    float mIntegral;
    float mDiff_prev;
}

#endif  // PID_CONTROL_H