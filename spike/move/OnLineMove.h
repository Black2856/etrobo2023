/*
クラス名:OnLineMove
作成日:2023/7/26
作成者:船田
*/
#ifndef ON_LINE_MOVE_H
#define ON_LINE_MOVE_H

#include "Manual.h"
#include "OnLineMove.h"
#include "Calc.h"
#include "DeviceInOut.h"
#include "PIDControl.h"

class OnLineMove{
public:
    OnLineMove();
    void first(float p, float i, float d);
    bool execute(float gain);
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    Manual manual;

    PIDControl pidControl;
    unit::calibration calibration;
};

#endif