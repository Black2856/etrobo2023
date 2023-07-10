/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#include "arg_info.h"

void arg_info_t::addFloatArg(float arg){
    this->floatArgs.push_back(arg);
    this->argIdx.push_back(0);
}
void arg_info_t::addStrArg(char* arg){
    this->strArgs.push_back(arg);
    this->argIdx.push_back(1);
}

std::list<int> arg_info_t::getArgIdx(){
    return this->argIdx;
}

std::list<float> arg_info_t::getFloatArgs(){
    return this->floatArgs;
}

std::list<char*> arg_info_t::getStrArgs(){
    return this->strArgs;
}
