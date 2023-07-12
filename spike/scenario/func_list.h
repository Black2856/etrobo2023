/*
 * 2023/07/10
 * hunada
 */
#ifndef FUNC_LIST_H
#define FUNC_LIST_H

#include "Judge.h"
#include "functional"

struct FuncList{
    //#<func_list>
std::function<bool(Judge& j)> list[7] = {
    [](Judge& j) {return j.milage.j(100) and j.time.j(1000 * 1000);},
    [](Judge& j) {return j.time.j(1500 * 1000);},
    [](Judge& j) {return j.time.j(1000 * 1000);},
    [](Judge& j) {return j.time.j(600 * 1000);},
    [](Judge& j) {return j.milage.j(100) and j.time.j(1000 * 1000);},
    [](Judge& j) {return j.time.j(1500 * 1000);},
    [](Judge& j) {return j.time.j(1000 * 1000);}
};
    //#</func_list>
};

#endif