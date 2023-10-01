/*
 * クラス名:ReadSig
 * 作成日:2023/09/28
 * 作成者:船田
 */

#ifndef READSIG_H
#define READSIG_H

#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "GeneralData.h"
#include "setting.h"
#include "unit.h"

//受信したファイルを解析してgeneralDataクラスに格納します
class ReadSig{
public:
    void main();

private:
    GeneralData& generalData = GeneralData::getInstance();

    //route.txt
    void storeRoute(const char* filePath);

    //minifigLabel.txt
    void storeMinifigLabel(const char* filePath);
};

#endif