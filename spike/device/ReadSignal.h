/*
 * クラス名:ReadSignal
 * 作成日:2023/09/28
 * 作成者:船田
 */

#ifndef READSIGNAL_H
#define READSIGNAL_H

#include <cstdio>
#include <fstream>
#include <stdio.h>

#include "GeneralData.h"
#include "setting.h"

//受信したファイルを解析してgeneralDataクラスに格納します
class ReadSignal{
public:
    void main();

private:
    GeneralData& generalData = GeneralData::getInstance();

    void processAndDeleteFile(const char* filePath);
    void concatenateStrings(char *result, const char *str1, const char *str2);
};

#endif