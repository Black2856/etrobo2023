/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#ifndef ARG_INFO_H
#define ARG_INFO_H

#include "execution.h"
#include <vector>

class arg_info_t{
private:
    //要素ごとにどちらの型を使用するかを決定する。0:floatArgs, 1:strArgs
    std::vector<int> argIdx;
    std::vector<float> floatArgs;
    std::vector<std::string> strArgs;
public:
    void addFloatArg(const float arg);
    void addStrArg(const std::string arg);

    vector<int> getArgIdx() const;
    vector<float> getFloatArg() const;
    vector<std::string> getStrArg() const;
}

#endif