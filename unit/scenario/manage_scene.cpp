/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#include "manage_scene.h"

Manage_scene::Manage_scene(std::string scenarioName){
    this->scenarioName = scenarioName;
}

void Manage_scene::makeCALL_SCENARIO(std::string arg1){
    arg_info_t argInfo;
    argInfo.addStrArg(arg1);
    
    Scene scene(Execution::CALL_SCENARIO, argInfo);
    scenario.push_back(scene);
}

void Manage_scene::makeTRACE(std::function<bool(Judge j)> transitionCondition, float arg1, float arg2, float arg3, float arg4){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);
    argInfo.addFloatArg(arg2);
    argInfo.addFloatArg(arg3);
    argInfo.addFloatArg(arg4);

    Scene scene(Execution::TRACE, argInfo, transitionCondition);
    scenario.push_back(scene);
}

void Manage_scene::makeSTOP(){
    arg_info_t argInfo;

    Scene scene(Execution::CALL_SCENARIO, argInfo);
    scenario.push_back(scene);
}

void Manage_scene::makeMANUAL(std::function<bool(Judge j)> transitionCondition, float arg1, float arg2){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);
    argInfo.addFloatArg(arg2);

    Scene scene(Execution::CALL_SCENARIO, argInfo);
    scenario.push_back(scene);
}

std::string Manage_scene::getName(){
    return this->scenarioName;
}

std::vector<Scene> Manage_scene::getScenes(){
    return this->scenario;
}