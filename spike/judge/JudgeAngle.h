/*
 * クラス名:JudgeAngle
 * 作成日:2023/06/03
 * 作成者:杉本
 */
#ifndef JUDGE_ANGLE_H
#define JUDGE_ANGLE_H

#include "JudgeNumerical.h"
#include "DeviceInOut.h"
#include "Calc.h"

class JudgeAngle : public JudgeNumerical{
public:
    JudgeAngle();

private:
    float getValue() const override;
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    
};

#endif  // JUDGE_ANGLE_H