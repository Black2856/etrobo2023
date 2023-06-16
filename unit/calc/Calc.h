/*
 * クラス名:Calc
 * 作成日：2023/06/07
 * 作成者:杉本
 */
#ifndef CALC_H
#define CALC_H

#include "Localization.h"
#include "RGBtoHSV.h"
#include "SpeedCorrection.h"

class Calc {
public:
    // インスタンス取得
    static Calc& getInstance();

    // 各種インスタンス
    Localization&   localization;
    RGBtoHSV        rgb2hsv;
    SpeedCorrection speedCorrection;

private:

    Calc(); // プライベートコンストラクタ
    static Calc* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Calc(Calc const&);
    void operator=(Calc const&);
};

#endif  // CALC_H