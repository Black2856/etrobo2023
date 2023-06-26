/*
 * 作成日:2023/06/26
 * 作成者:船田
 */

#include "manage_scenario.h"

void Manage_scenario::add(Manage_scene manageScene){
    this->scenarioList.push_back(manageScene);
}

void Manage_scenario::update(){
    this->compileScene.clear();
    //mainシーン管理を追加
    Manage_scene& ms = findScenario("main");
    if(ms != NULL){
        addScene(ms);
    }else{
        printf("mainシーンが存在しません");
    }
}

bool Manage_scenario::execute(){
    Execution execution = this->compileScene[this->executeIdx].getExecution();

    //各動作による呼び出し処理
    switch(execution){
        case Execution::CALL_SCENARIO:
            printf("この実行は選択されません");
            break;
        case Execution::MANUAL:
            break;
        case Execution::STOP:
            break;
        case Execution::TRACE:
            break;
    }

    //遷移条件
    if(true == this->compileScene[this->executeIdx].judgement()){
        this->executeIdx ++;
    }

    //終端かどうか
    if(this->compileScene.max_size() - 1 < this->executeIdx){
        return true; //終了
    }else{
        return false;
    }
}

void Manage_scenario::addScene(const Manage_scene& manageScene){
    vector<Scene> scenes = manageScene.getScenes(); //scene配列の取得
    for(Scene& x : this->scenes){
        if(x.getExecution == Execution::CALL_SCENARIO){ //実行がCALL_SCENARIOの場合再帰呼び出し
            arg_info_t args = x.getArgInfo();
            Manage_scene& ms = findScenario(args.strArgs[0]);
            addScene(ms); //CALL_SCENARIOのsceneの名前でシナリオを検索したものを追加する
        }else{
            this->compileScene.push_back(x);
        }
    }
}

Manage_scene& Manage_scenario::findScenario(const std::string name){
    for(Manage_scene& x : this->scenarioList){
        if(x.getName() == name){
            return x;
        }
    }
    printf("見つかりませんでした。");
}