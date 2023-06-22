/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef SCENE_H
#define SCENE_H

#include "execution.h"
#include <vector>
#include <functional>

class Scene{
public:
    void addFloatArg(const float floatArg);
    void addStringArg(const std::string strArg);
    void getArg(const uint8_t idxArg) const;

private:
    std::vector<float> floatArgs;
    std::vector<std::string> strArgs;
    //要素ごとにどちらの型を使用するかを決定する。0:floatArgs, 1:strArgs
    std::vector<uint8_t> idxArgs;
    std::function<void()> transitionCondition;
    Execution execution;
};

#endif