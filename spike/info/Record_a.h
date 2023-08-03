/*
 * クラス名:Record
 * 作成日:2023/08/02
 * 作成者:船田
 */
#ifndef RECORD_H
#define RECORD_H

#include "SensorData.h"
#include "setting.h"
#include <list>

class Record {
public:
    // インスタンス取得
    static Record& getInstance();

    SensorData sensorData;

    SensorData getSensorData(int idx);
    int getRecordLimit();
    void appendSensorData();

private:
    std::list<SensorData> sensorList;
    std::list<int> runRoute;
    int recordLimit;

    void initRecordList();

    Record(); // プライベートコンストラクタ
    static Record* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Record(Record const&);
    void operator=(Record const&);
};

#endif