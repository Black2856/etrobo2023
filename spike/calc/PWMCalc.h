/*
クラス名:PWMCalc
作成日:2023/07/19
作成者:船田
*/
#ifndef PWM_CALC_H
#define PWM_CALC_H

#include "SpeedCorrection.h"
#include "JudgeData.h"
#include <cmath>

class PWMCalc{
public:
    PWMCalc();
    int changePWM();
    void setPWM(int pwm, float progThreshold);

private:
    int beforePWM;
    float progThreshold;
    SpeedCorrection speedCorrectionIn;
    SpeedCorrection speedCorrectionOut;

    JudgeData& judgeData = JudgeData::getInstance();
};

#endif //PWM_CALC_H