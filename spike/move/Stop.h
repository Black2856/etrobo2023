/*
クラス名:Stop
作成日:2023/07/21
作成者:船田
*/
#ifndef STOP_H
#define LINE_TRACE_H

#include "DeviceInOut.h"

class Stop {
public:
    Stop();
    void first();
private:
    DeviceInOut& device;
};

#endif  // LINE_TRACE_H