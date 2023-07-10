/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#include "scene.h"

Scene::Scene(Execution execution, arg_info_t argInfo, int stateTransition){
    this->argInfo = argInfo;
    this->execution = execution;
    this->stateTransition = stateTransition;
};

Scene::Scene(Execution execution, arg_info_t argInfo){
    this->argInfo = argInfo;
    this->execution = execution;
}

arg_info_t Scene::getArgInfo() const{
    return this->argInfo;
}

Execution Scene::getExecution() const{
    return this->execution;
}

int Scene::getStateTransition() const{
    return this->stateTransition;
}