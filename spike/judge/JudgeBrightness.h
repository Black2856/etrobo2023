/*
 * クラス名:JudgeBrightness
 * 作成日:2023/09/29
 * 作成者:船田
 */
#ifndef JUDGE_BRIGHTNESS_H
#define JUDGE_BRIGHTNESS_H

#include "JudgeNumerical.h"
#include "DeviceInOut.h"
#include "GeneralData.h"

class JudgeBrightness : public JudgeNumerical{
public:
    JudgeBrightness();

private:
    float getValue() const override;
    bool  isTargetReached() const override;

    GeneralData& generalData = GeneralData::getInstance();
    DeviceInOut& device;
};

#endif  // JUDGE_BRIGHTNESS_H