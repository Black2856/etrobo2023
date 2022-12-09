/*
簡易的な数値データを出力する。
addData(列名、データ)で列名に相当する行にデータを格納する。　※行データは２つ以上格納できずに上書きされる。
dataOutput(ファイル名)でaddDataで格納したデータ一行分を出力する。
*/

#ifndef DATAIO_H
#include "Clock.h"
#include "string"
#include "stdio.h"
#include "string.h"

using namespace std;
using namespace ev3api;

class DataIO{ //ファイル出力のSingletonクラス
public:
    static DataIO* getInstance();

    void addData(const char *column, const char *val); //データ配列に追加(呼び出し用)
    void addData(const char *column, const int val);
    void addData(const char *column, const float val);
    void addData(const char *column, const double val);

    void dataOutput(const char *fileName); //データ配列をファイルに出力(1行)

    static void fileOutput(const char *fileName, const char *text); //特定文字列をファイルに出力
private:
    Clock clock;

    DataIO();
    ~DataIO();
    static DataIO* m_DataIO;

    int addedData = 0; //0:更新なし 1:行データの書き込みあり 2:行及び列データの書き込みあり
    int columnIndex = 1;
    int dataSize = 30;
    char column[30][20]; 
    char row[30][20];

    void addDataProcess(const char *column, const char *str); //データ配列に追加
};

#define DATAIO_H
#endif