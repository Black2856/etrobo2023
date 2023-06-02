/*
 * クラス名:JudgeTime
 * 作成日：2023/05/19
 * 作成者:杉本
 */
#ifndef _JUDGE_TIME_H_
#define _JUDGE_TIME_H_

#include "JudgeNumerical.h"
#include "DeviceInOut.h"

class JudgeTime : public JudgeNumerical{
public:
    JudgeTime();

private:
    float getValue() const override;
    DeviceInOut& device;
};

#endif  // _JUDGE_TIME_H_