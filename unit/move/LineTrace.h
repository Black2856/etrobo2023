/*
クラス名:LineTrace
作成日:2023/06/26
作成者:松尾
*/
#ifndef LINE_TRACE_H
#define LINE_TRACE_H

#include "unit.h"
#include "PIDControl.h"
#include "DeviceInOut.h"

class LineTrace {
public:
    LineTrace();
    void Trace(int pwm);
private:
    unit::pid_t mPID;
    PIDControl pidControl;
    DeviceInOut& device;
};

#endif  // LINE_TRACE_H