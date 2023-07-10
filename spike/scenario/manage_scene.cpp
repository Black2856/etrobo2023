/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#include "manage_scene.h"

Manage_scene::Manage_scene(char* scenarioName){
    this->scenarioName = scenarioName;
}

void Manage_scene::makeCALL_SCENARIO(char* arg1){
    arg_info_t argInfo;
    argInfo.addStrArg(arg1);
    
    Scene scene(Execution::CALL_SCENARIO, argInfo);
    scenario.push_back(scene);
}

void Manage_scene::makeSTOP(){
    arg_info_t argInfo;

    Scene scene(Execution::CALL_SCENARIO, argInfo);
    scenario.push_back(scene);
}

char* Manage_scene::getName(){
    return this->scenarioName;
}

std::list<Scene> Manage_scene::getScenes(){
    return this->scenario;
}