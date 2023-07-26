/*
クラス名:Stop
作成日:2023/07/21
作成者:船田
*/
#ifndef STOP_H
#define LINE_TRACE_H

#include "DeviceInOut.h"
#include "Calc.h"

class Stop {
public:
    Stop();
    void first(float pwmTransitionTime);
    bool execute(float pwmTransitionTime);
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
};

#endif  // LINE_TRACE_H