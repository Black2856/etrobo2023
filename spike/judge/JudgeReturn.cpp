/*
 * クラス名:JudgeReturn
 * 作成日:2023/07/21
 * 作成者:船田
 */
#include "JudgeReturn.h"

JudgeReturn::JudgeReturn():
    device(DeviceInOut::getInstance()){
}

bool JudgeReturn::j(bool flag){
    return this->flag == flag;
}

void JudgeReturn::setFlag(bool flag){
    this->flag = flag;
}

void JudgeReturn::reset(){
    this->flag = false;
}