/*
 * クラス名:JudgeAngleMinifig
 * 作成日:2023/09/29
 * 作成者:船田
 */

#ifndef JUDGE_ANGLE_MINIFIG_H
#define JUDGE_ANGLE_MINIFIG_H

#include "JudgeNumerical.h"
#include "DeviceInOut.h"
#include "Localization.h"
#include "GeneralData.h"
#include "setting.h"

class JudgeAngleMinifig : public JudgeNumerical{
public:
    JudgeAngleMinifig();

private:
    float getValue() const override;
    float targetConvert(float target) const override;

    GeneralData& generalData = GeneralData::getInstance();
    DeviceInOut& device;
    Localization& localization;
    
};

#endif  // JUDGE_ANGLE_MINIFIG_H