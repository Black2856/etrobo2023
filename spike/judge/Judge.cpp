/*
 * クラス名:Judge
 * 作成日:2023/06/07
 * 作成者:杉本
 */
#include "Judge.h"

Judge* Judge::instance = NULL;

Judge::Judge() {
    }

Judge& Judge::getInstance() {
    if (!instance) {
        instance = new Judge();
    }
    return *instance;
}

void Judge::allReset(){
    this->angle.stop();
    this->angleMinifig.stop();
    this->brightness.stop();
    this->mileage.stop();
    this->sonar.stop();
    this->time.stop();
    this->ret.reset();
}