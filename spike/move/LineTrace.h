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
#include "Calc.h"

class LineTrace {
public:
    LineTrace();
    void first(float pwm, float kp, float ki, float kd, float pwmTransitionTime);
    void trace(float pwm, float kp, float ki, float kd, float pwmTransitionTime);
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    PIDControl pidControl;
    unit::calibration calibration;
};

#endif  // LINE_TRACE_H