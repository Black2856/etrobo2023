/*
 * クラス名:Judge
 * 作成日:2023/08/02
 * 作成者:船田
 */
#ifndef RECORD_H
#define RECORD_H

#include "unit.h"
#include <list>

class Record {
public:
    // インスタンス取得
    static Record& getInstance();

private:
    std::list<unit::sensor_t> sensorData;
    std::list<int> runRoute;
    int recordLimit;

    Record(); // プライベートコンストラクタ
    static Record* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Record(Record const&);
    void operator=(Record const&);
};

#endif