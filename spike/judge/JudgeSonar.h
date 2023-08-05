/*
 * クラス名:JudgeSonar
 * 作成日:2023/06/03
 * 作成者:杉本
 */
#ifndef JUDGE_SONAR_H
#define JUDGE_SONAR_H

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

#endif  // JUDGE_SONAR_H