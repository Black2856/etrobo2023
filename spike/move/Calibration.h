/*
クラス名:Calibration
作成日:2023/7/26
作成者:
*/
#ifdef CALIBRATION_H
#define CALIBRATION_H

#include "Manual.h"
#include "OnLineMove.h"
#include "Calc.h"
#include "DeviceInOut.h"

class Calibration {
public:
    Calibration();
    bool execute(float pwm);
    
private:
    void getFase();
    void onLineFase();

    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    unit::calibration calibration;
    Manual manual;
};

#endif