/*
 * クラス名:Judge
 * 作成日：2023/06/07
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
