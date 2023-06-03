/*
 * クラス名:JudgeSonar
 * 作成日：2023/06/03
 * 作成者:杉本
 */
#ifndef _JUDGE_SONAR_H_
#define _JUDGE_SONAR_H_

#include "JudgeNumerical.h"
#include "DeviceInOut.h"

class JudgeSonar : public JudgeNumerical{
public:
    JudgeSonar();

private:
    float getValue() const override;
    bool  isTargetReached() const override;
    DeviceInOut& device;
};

#endif  // _JUDGE_SONAR_H_