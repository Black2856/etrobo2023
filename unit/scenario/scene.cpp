/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#include "scene.h"

void Scene::addFloatArg(const float floatArg){
    this->floatArgs.push_back(floatArg);
    this->idxArgs.push_back(0);  // floatを追加したので、0を追加
}
void Scene::addStringArg(const std::string strArg){
    this->floatArgs.push_back(strArg);
    this->idxArgs.push_back(1);  // stringを追加したので、1を追加
}
void Scene::getArg(const uint8_t idxArg) const{
    if(idxArg == 0){ //float型
        
    }else if(idxArg == 1){ //string型

    }else{
        printf("ERROR:指定種類ではない型です。[Scene::getArg]");
    }
}