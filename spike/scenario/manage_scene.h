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
    Manage_scene(char* scenarioName);

    void makeCALL_SCENARIO(char* arg1);
    template <typename F>
    void makeTRACE(F transitionCondition, float arg1, float arg2, float arg3, float arg4){
        arg_info_t argInfo;
        argInfo.addFloatArg(arg1);
        argInfo.addFloatArg(arg2);
        argInfo.addFloatArg(arg3);
        argInfo.addFloatArg(arg4);

        Scene scene(Execution::TRACE, argInfo, transitionCondition);
        scenario.push_back(scene);
    };
    void makeSTOP();
    template <typename F>
    void makeMANUAL(F transitionCondition, float arg1, float arg2){
        arg_info_t argInfo;
        argInfo.addFloatArg(arg1);
        argInfo.addFloatArg(arg2);

        //Scene scene(Execution::CALL_SCENARIO, argInfo);
        //scenario.push_back(scene);
    };
    template <typename F>
    void test(F a){
        printf("a");
        unit::judge u;
        a(u);
    };

    char* getName();
    std::list<Scene> getScenes();
private:
    char* scenarioName;
    std::list<Scene> scenario;
};

#endif