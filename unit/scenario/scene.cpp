/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#include "scene.h"

Scene::Scene(Execution execution, arg_info_t argInfo, std::function<bool(Judge j)> transitionCondition){
    this->transitionCondition = transitionCondition;
    this->argInfo = argInfo;
    this->execution = execution;
}

Scene::Scene(Execution execution, arg_info_t argInfo){
    this->argInfo = argInfo;
    this->execution = execution;
}

arg_info_t Scene::getArgInfo() const{
    return argInfo;
}

Execution Scene::getExecution() const{
    return execution;
}

bool Scene::judgement(const Judge j) const{
    return true;
}