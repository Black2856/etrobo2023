/*
 * クラス名:Manual
 * 作成日:2023/07/24
 * 作成者:船田
 */
#ifndef MANUAL_H
#define MANUAL_H

#include "Calc.h"
#include "PIDControl.h"
#include "unit.h"

enum class RunType {
    STRAIGHT = 1,
    CENTER_ROTATION = 2,
    LEFT_WHEEL_ROTATION = 3,
    RIGHT_WHEEL_ROTATION = 4
};

class Manual {
public:
    Manual();
    void setPWM(float pwm, float pwmTransitionTime);

    void first(RunType runType, float pwm, float pwmTransitionTime);
    void execute();

private:
    void straight();
    void centerRotation();
    void wheelRotation(int wheel);

    //基準の車体角度
    float standardDirection1;
    float standardDirection2;
    PIDControl straightPID;
    RunType runType;

    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
};

#endif  // MANUAL_H