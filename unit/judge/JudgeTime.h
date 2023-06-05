/*
 * クラス名:JudgeTime
 * 作成日：2023/05/19
 * 作成者:杉本
 */
#ifndef JUDGE_TIME_H
#define JUDGE_TIME_H

#include "JudgeNumerical.h"
#include "DeviceInOut.h"

class JudgeTime : public JudgeNumerical{
public:
    JudgeTime();

private:
    float getValue() const override;
    DeviceInOut& device;
};

#endif  // JUDGE_TIME_H