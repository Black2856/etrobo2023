/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef SCENE_H
#define SCENE_H

#include "Judge.h"
#include "execution.h"
#include "arg_info.h"
#include <vector>
#include <functional>

class Scene{
public:
    Scene(Execution execution, arg_info_t argInfo, std::function<bool(const Judge& j)> transitionCondition);
    Scene(Execution execution, arg_info_t argInfo);

    arg_info_t getArgInfo() const;
    Execution getExecution() const;
    bool judgement(const Judge& j) const;

private:
    arg_info_t argInfo;
    std::function<bool(const Judge& j)> transitionCondition;
    Execution execution;
};

#endif