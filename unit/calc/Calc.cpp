/*
 * クラス名:Calc
 * 作成日：2023/06/07
 * 作成者:杉本
 */
#include "Calc.h"

Calc* Calc::instance = NULL;

Calc::Calc():
    localization(Localization::getInstance()) {
    }

Calc& Calc::getInstance() {
    if (!instance) {
        instance = new Calc();
    }
    return *instance;
}
