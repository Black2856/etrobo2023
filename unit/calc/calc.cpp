/*
 * クラス名:calc
 * 作成日：2023/06/07
 * 作成者:杉本
 */
#include "calc.h"

calc* calc::instance = NULL;

calc::calc():
    localization(Localization::getInstance()) {
    }

calc& calc::getInstance() {
    if (!instance) {
        instance = new calc();
    }
    return *instance;
}
