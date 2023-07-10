/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef SCENE_H
#define SCENE_H

#include "execution.h"
#include "arg_info.h"
#include <functional>

class Scene{
public:
    Scene(Execution execution, arg_info_t argInfo, int transitionCondition);
    Scene(Execution execution, arg_info_t argInfo);

    arg_info_t getArgInfo() const;
    Execution getExecution() const;
    int getTransitionCondition() const;

private:
    arg_info_t argInfo;
    int transitionCondition;
    Execution execution;
};

#endif