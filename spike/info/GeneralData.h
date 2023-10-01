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

    unit::calibration_t getBrightness();
    void setBrightness(unit::calibration_t brightness);

    unit::calibration_t getColor();
    void setColor(unit::calibration_t color);

    //受信したかどうか, idx = {ブロックdeトレジャー走行ルート, ミニフィグ写真の相対角度}
    bool getIsData(int idx);

    int getMinifigDegree();
    void setMinifigDegree(int degree);

    std::list<int> getRunRoute();
    void setRunRoute(std::list<int> runRoute);

private:
    //キャリブレーションデータ
    unit::calibration_t brightness;
    unit::calibration_t color;
    
    //受信したかどうか (ブロックdeトレジャー走行ルート, ミニフィグ写真の相対角度)
    bool isData[2] = {false, false};

    //ブロックdeトレジャー走行ルート
    std::list<int> runRoute;

    // ミニフィグ写真の相対角度()
    int minifigDegree = 0;

    GeneralData(); // プライベートコンストラクタ
    static GeneralData* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    GeneralData(GeneralData const&);
    void operator=(GeneralData const&);
};

#endif