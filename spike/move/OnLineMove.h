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

class OnLineMove{
public:
    OnLineMove();
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    unit::calibration calibration;
    Manual manual;
};

#endif