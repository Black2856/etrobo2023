/*
 * クラス名:JudgeColor
 * 作成日:2023/08/25
 * 作成者:船田
 */
#ifndef JUDGE_COLOR_H
#define JUDGE_COLOR_H

#include "RGBtoHSV.h"
#include "DeviceInOut.h"
#include "unit.h"
#include "GeneralData.h"

class JudgeColor{
public:
    JudgeColor();
    bool j(unit::color_t color);

private:
    GeneralData& generalData = GeneralData::getInstance();
    DeviceInOut& device;
    RGBtoHSV rgb2hsv;

    unit::color_t getColor();
};

#endif  // JUDGE_COLOR_H