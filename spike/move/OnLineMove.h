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
#include "GeneralData.h"
#include "PIDControl.h"

class OnLineMove{
public:
    OnLineMove();
    void first(int maxPWM, float p, float i, float d);
    bool execute();
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    GeneralData& generalData = GeneralData::getInstance();
    Manual manual;

    int maxPWM;
    PIDControl pidControl;
    unit::calibration_t calibration;
};

#endif