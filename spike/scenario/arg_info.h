/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#ifndef ARG_INFO_H
#define ARG_INFO_H

#include "execution.h"
#include "unit.h"
#include <list>

class arg_info_t{
private:
    //要素ごとにどちらの型を使用するかを決定する。0:floatArgs, 1:strArgs
    std::list<int> argIdx;
    std::list<float> floatArgs;
    std::list<const char*> strArgs;

public:
    void addFloatArg(float arg);
    void addStrArg(const char* arg);

    std::list<int> getArgIdx();
    float getFloatArg(int idx);
    const char* getStrArg(int idx);
};

#endif