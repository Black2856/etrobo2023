/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef MANAGE_SCENE_H
#define MANAGE_SCENE_H

#include "scene.h"
#include "arg_info.h"
#include "execution.h"
#include "unit.h"
#include <list>
#include <functional>

class Manage_scene{
public:
    Manage_scene(const char* scenarioName);

    void makeCALL_SCENARIO(const char* arg1);
    void makeTRACE(int stateTransition, float arg1, float arg2, float arg3, float arg4);
    void makeSTOP(int stateTransition);
    void makeMANUAL(int stateTransition, float arg1, float arg2);

    const char* getName();
    std::list<Scene> getScenes();
private:
    const char* scenarioName;
    std::list<Scene> scenario;
};

#endif