/*
クラス名:PWMCalc
作成日:2023/07/19
作成者:船田
*/
#ifndef PWM_CALC_H
#define PWM_CALC_H

#include "SpeedCorrection.h"

class PWMCalc{
public:
    PWMCalc();
    int changePWM();
    void setPWM(int pwm, float time);

private:
    int beforePWM;

    SpeedCorrection speedCorrection;
};

#endif //PWM_CALC_H