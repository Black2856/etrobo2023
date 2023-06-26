/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef MANAGE_SCENE_H
#define MANAGE_SCENE_H

#include "scene.h"
#include "arg_info.h"
#include "execution.h"
#include <vector>
#include <functional>

class Manage_scene{
public:
    Manage_scene(std::string scenarioName);

    void makeCALL_SCENARIO(std::string arg1);
    void makeTRACE(std::function<bool(Judge j)> transitionCondition, float arg1, float arg2, float arg3, float arg4);
    void makeSTOP();
    void makeMANUAL(std::function<bool(Judge j)> transitionCondition, float arg1, float arg2);
    
    std::string getName();
    std::vector<Scene> getScenes();
private:
    std::string scenarioName;
    std::vector<Scene> scenario;
};

#endif