/*
 * クラス名:JudgeTouch
 * 作成日:2023/07/21
 * 作成者:松尾
 */
#ifndef JUDGE_TOUCH_H
#define JUDGE_TOUCH_H

#include "JudgeNumerical.h"
#include "DeviceInOut.h"

class JudgeTouch :public JudgeNumerical{
public:
    JudgeTouch();
private:
    float getValue() const override;
    DeviceInOut& device;
};

#endif  // JUDGE_ANGLE_H