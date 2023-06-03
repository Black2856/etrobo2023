/*
 * クラス名:JudgeAngle
 * 作成日：2023/06/03
 * 作成者:杉本
 */
#ifndef _JUDGE_ANGLE_H_
#define _JUDGE_ANGLE_H_

#include "JudgeNumerical.h"
#include "DeviceInOut.h"

class JudgeAngle : public JudgeNumerical{
public:
    JudgeAngle();

private:
    float getValue() const override;
    bool  isTargetReached() const override;
    DeviceInOut& device;
};

#endif  // _JUDGE_ANGLE_H_