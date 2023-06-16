/*
 * クラス名:calc
 * 作成日：2023/06/07
 * 作成者:杉本
 */
#ifndef CALC_H
#define CALC_H

#include "Localization.h"
#include "RGBtoHSV.h"
#include "SpeedCorrection.h"

class calc {
public:
    // インスタンス取得
    static calc& getInstance();

    // 各種インスタンス
    Localization    localization;
    RGBtoHSV        rgb2hsv;
    SpeedCorrection speedCorrection;

private:

    calc(); // プライベートコンストラクタ
    static calc* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    calc(calc const&);
    void operator=(calc const&);
};

#endif  // CALC_H