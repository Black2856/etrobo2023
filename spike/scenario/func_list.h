/*
 * 作成日:2023/07/10
 * 作成者:船田
 */
#ifndef FUNC_LIST_H
#define FUNC_LIST_H

#include "Judge.h"
#include <functional>

struct FuncList{
    std::function<bool(Judge& j)> list[3] = {
        [](Judge& j) {return j.judgeTime.judge(5000 * 1000);},
        [](Judge& j) {return j.judgeTime.judge(10000 * 1000);},
        [](Judge& j) {return j.judgeMileage.judge(100);}
    };
};

#endif