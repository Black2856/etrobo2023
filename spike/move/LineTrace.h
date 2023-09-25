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
#include "GeneralData.h"
#include "Calc.h"
#include "RGBtoHSV.h"

class LineTrace {
public:
    LineTrace();
    void setPWM(float pwm, float pwmTransitionTime);

    void first(float pwm, float kp, float ki, float kd, float pwmTransitionTime);
    void trace();
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    Record& record = Record::getInstance();
    GeneralData& generalData = GeneralData::getInstance();
    PIDControl pidControl;
    RGBtoHSV rgb2hsv;
    unit::calibration_t brightness;
    unit::calibration_t color;
    
};

#endif  // LINE_TRACE_H