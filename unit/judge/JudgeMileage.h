/*
 * クラス名:JudgeTime
 * 作成日：2023/05/28
 * 作成者:杉本
 */
#ifndef _JUDGE_MILEAGE_H_
#define _JUDGE_MILEAGE_H_

#include "JudgeNumerical.h"
#include "Localization.h"

class JudgeMileage : public JudgeNumerical{
public:
    JudgeMileage();

private:
    float getValue() const override;
    Localization& localization;
};

#endif  // _JUDGE_MILEAGE_H_