/*
 * 作成日:2023/06/25
 * 作成者:船田
 */
#include "arg_info.h"

void arg_info_t::addFloatArg(const float arg){
    this->floatArgs.push_back(arg);
    this->argIdx.push_back(0);
}
void arg_info_t::addStrArg(const std::string arg){
    this->strArgs.push_back(arg);
    this->argIdx.push_back(1);
}

std::vector<int> arg_info_t::getArgIdx() const{
    return this->argIdx;
}
std::vector<float> arg_info_t::getFloatArg() const{
    return this->floatArgs;
}
std::vector<std::string> arg_info_t::getStrArg() const{
    return this->strArgs;
}
