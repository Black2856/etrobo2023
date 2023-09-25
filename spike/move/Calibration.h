/*
クラス名:Calibration
作成日:2023/7/26
作成者:船田
*/
#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "Calc.h"
#include "DeviceInOut.h"
#include "Record.h"
#include "GeneralData.h"
#include "SensorData.h"
#include "unit.h"
#include "RGBtoHSV.h"
#include "ev3api.h"

#include <cstring>
#include <list>

//バックグラウンド動作
class Calibration {
public:
    Calibration();
    void first(const char* command); //"record:type":記録の開始, "stop":停止してキャリブレーション値の上書き
    void execute();

    bool getState();
private:
    void stop();

    int recordType = 0; //1:反射光, 2:カラーセンサー(V値)
    bool state = false; //実行状態
    DeviceInOut& device;
    Record& record = Record::getInstance();
    Calc& calc = Calc::getInstance();
    GeneralData& generalData = GeneralData::getInstance();
    RGBtoHSV rgb2hsv;
};

#endif