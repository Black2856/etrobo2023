/*
 * クラス名:JudgeColor
 * 作成日：2023/06/03
 * 作成者:杉本
 */
#ifndef JUDGE_COLOR_H
#define JUDGE_COLOR_H

#include "JudgeNumerical.h"
#include "走行記録.h"
#include "unit.h"

class JudgeColor {
public:
    JudgeColor();

    bool judge(unit::color_t);

private:
    走行記録& 記録;
};

#endif  // JUDGE_COLOR_H