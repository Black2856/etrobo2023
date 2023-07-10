/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef SCENE_H
#define SCENE_H

#include "Judge.h"
#include "execution.h"
#include "arg_info.h"
#include "unit.h"
#include <vector>
#include <functional>

class Scene{
public:
    template<typename F>
    Scene(Execution execution, arg_info_t argInfo, F transitionCondition){
        unit::judge a;
        this->argInfo = argInfo;
        this->execution = execution;

    };
    Scene(Execution execution, arg_info_t argInfo);

    arg_info_t getArgInfo() const;
    Execution getExecution() const;
    bool judgement(unit::judge j) const;

private:
    arg_info_t argInfo;
    std::function<bool(unit::judge)> transitionCondition;
    Execution execution;
};

#endif