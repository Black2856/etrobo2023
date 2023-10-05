/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#include "manage_scene.h"

Manage_scene::Manage_scene(const char* scenarioName){
    this->scenarioName = scenarioName;
}

void Manage_scene::makeTRACE(int stateTransition, float arg1, float arg2, float arg3, float arg4, float arg5){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);
    argInfo.addFloatArg(arg2);
    argInfo.addFloatArg(arg3);
    argInfo.addFloatArg(arg4);
    argInfo.addFloatArg(arg5);

    Scene scene(Execution::TRACE, argInfo, stateTransition);
    this->scenario.push_back(scene);
};

void Manage_scene::makeCALL_SCENARIO(const char* arg1){
    arg_info_t argInfo;
    argInfo.addStrArg(arg1);
    
    Scene scene(Execution::CALL_SCENARIO, argInfo);
    this->scenario.push_back(scene);
}

void Manage_scene::makeSTOP(int stateTransition, float arg1){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);

    Scene scene(Execution::STOP, argInfo, stateTransition);
    this->scenario.push_back(scene);
}

void Manage_scene::makeMANUAL(int stateTransition, float arg1, float arg2, float arg3){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);
    argInfo.addFloatArg(arg2);
    argInfo.addFloatArg(arg3);

    Scene scene(Execution::MANUAL, argInfo, stateTransition);
    this->scenario.push_back(scene);
};

void Manage_scene::makeMANUAL_PID(int stateTransition, float arg1, float arg2, float arg3){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);
    argInfo.addFloatArg(arg2);
    argInfo.addFloatArg(arg3);

    Scene scene(Execution::MANUAL_PID, argInfo, stateTransition);
    this->scenario.push_back(scene);
}

void Manage_scene::makeCALIBRATION(const char* arg1){
    arg_info_t argInfo;
    argInfo.addStrArg(arg1);

    Scene scene(Execution::CALIBRATION, argInfo);
    this->scenario.push_back(scene);
}

void Manage_scene::makeTAKE_PHOTO(int stateTransition, float arg1){
    arg_info_t argInfo;
    argInfo.addFloatArg(arg1);

    Scene scene(Execution::TAKE_PHOTO, argInfo, stateTransition);
    this->scenario.push_back(scene);
}

const char* Manage_scene::getName() const{
    return this->scenarioName;
}

std::list<Scene> Manage_scene::getScenes(){
    return this->scenario;
}