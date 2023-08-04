/*
クラス名:ManualPID
作成日:2023/7/26
作成者:船田
*/
#ifndef ON_LINE_MOVE_H
#define ON_LINE_MOVE_H

#include "Manual.h"
#include "ManualPID.h"
#include "Calc.h"
#include "DeviceInOut.h"
#include "GeneralData.h"
#include "PIDControl.h"

#include <cmath>

namespace manualPID {
    enum class RunType {
        STRAIGHT = 1,
        CENTER_ROTATION = 2,
        LEFT_WHEEL_ROTATION = 3,
        RIGHT_WHEEL_ROTATION = 4,
        ON_LINE_MOVE = 5
    };
}

class ManualPID{
public:
    ManualPID();
    void first(manualPID::RunType runType, float maxPWM, float transitionValue);
    bool execute();
private:
    float distance();
    float direction();
    float onLineMove();

    //valueが ±maxを超えていたらor下回っていたら、maxにする
    float max(float value, float max);

    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    GeneralData& generalData = GeneralData::getInstance();
    Manual manual;

    manualPID::RunType runType;
    int maxPWM;
    float rotation;
    PIDControl pidControl;
    unit::calibration_t calibration;

    float transitionValue;
    float standardDistance;
    float standardDirection;
};

#endif