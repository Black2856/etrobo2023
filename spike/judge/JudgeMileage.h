/*
 * クラス名:JudgeTime
 * 作成日:2023/05/28
 * 作成者:杉本
 */
#ifndef JUDGE_MILEAGE_H
#define JUDGE_MILEAGE_H

#include "JudgeNumerical.h"
#include "Localization.h"

class JudgeMileage : public JudgeNumerical{
public:
    JudgeMileage();

private:
    float getValue() const override;
    Localization& localization;
};

#endif  // JUDGE_MILEAGE_H