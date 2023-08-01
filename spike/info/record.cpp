/*
 * クラス名:Judge
 * 作成日:2023/08/02
 * 作成者:船田
 */
#include "record.h"

Record* Record::instance = NULL;

Record::Record(){
}

Record& Record::getInstance() {
    if (!instance) {
        instance = new Record();
    }
    return *instance;
}
