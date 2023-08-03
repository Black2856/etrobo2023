/*
 * クラス名:GeneralData
 * 作成日:2023/08/02
 * 作成者:船田
 */

#ifndef GENERAL_DATA_H
#define GENERAL_DATA_H

#include "unit.h"

class GeneralData {
public:
    // インスタンス取得
    static GeneralData& getInstance();

    unit::calibration_t getCalibration();
    void setCalibration(unit::calibration_t calibration);

private:
    unit::calibration_t calibration;
    std::list<int> runRoute; //恐らく型を変更する

    GeneralData(); // プライベートコンストラクタ
    static GeneralData* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    GeneralData(GeneralData const&);
    void operator=(GeneralData const&);
};

#endif