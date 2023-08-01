/*
クラス名:Calibration
作成日:2023/7/26
作成者:船田
*/
#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "OnLineMove.h"
#include "Calc.h"
#include "DeviceInOut.h"
#include "unit.h"

#include <string.h>

//バックグラウンド動作
class Calibration {
public:
    Calibration();
    void first(const char* command); //"record":記録の開始, "stop":停止してキャリブレーション値の上書き
    void record();

    bool getState();
private:
    void stop();

    bool state = false; //実行状態
    Calc& calc = Calc::getInstance();
    unit::calibration calibration;
};

#endif