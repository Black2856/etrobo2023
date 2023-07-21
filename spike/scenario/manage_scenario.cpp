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

    Manage_scene* ms = findScenario("main");
    if(ms != nullptr){
        this->addScene(*ms);
        printf("*シナリオ管理:コンパイル完了*\n");
    }else{
        printf("error at Manage_scenario::update() : mainが存在しません");
    }
}

void Manage_scenario::addScene(Manage_scene& manageScene){
    const std::list<Scene> scenes = manageScene.getScenes(); // scene配列の取得
    for(const Scene& x : scenes){
        if(x.getExecution() == Execution::CALL_SCENARIO){ // 実行がCALL_SCENARIOの場合再帰呼び出し
            arg_info_t args = x.getArgInfo();
            const char* name = args.getStrArg(0);
            Manage_scene* ms = findScenario(name);
            addScene(*ms); // CALL_SCENARIOのsceneの名前でシナリオを検索したものを追加する
        }else{
            this->compileScene.push_back(x);
        }
    }
}

Manage_scene* Manage_scenario::findScenario(const char* name){
    for(Manage_scene& x : this->scenarioList){
        if(std::strcmp(x.getName(), name) == 0){
            Manage_scene* ptr = new Manage_scene(x);
            return ptr;
        }
    }
    return nullptr;
}

bool Manage_scenario::execute(){
    //終端かどうか
    if(this->compileScene.size() - 1 < this->executeIdx){
        return true; //終了
    }

    //Secne情報の取得
    Scene nowScene = unit::getList(this->compileScene, this->executeIdx);
    Execution execution = nowScene.getExecution();
    arg_info_t argInfo = nowScene.getArgInfo();

    //各動作による呼び出し処理
    if(this->isFirst == true){
        this->first(execution, argInfo);
        this->isFirst = false;
    }
    
    bool flag = this->intermediate(execution, argInfo);
    //動作の返り値を判定に入れる
    Judge& j = Judge::getInstance();
    j.ret.setFlag(flag);

    //遷移条件
    if(true == stateTransition.judge(nowScene.getStateTransition())){
        this->end(execution, argInfo);

        this->isFirst = true;
        this->executeIdx ++;
        printf("*遷移 => %d*\n", this->executeIdx);
    }

    //終端かどうか
    if(this->compileScene.size()-1 < this->executeIdx){
        printf("*終了*\n");
        return true; //終了
    }else{
        return false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Manage_scenario::first(Execution& execution, arg_info_t& argInfo){
    switch(execution){
        case Execution::TRACE:
            this->lineTrace.first(argInfo.getFloatArg(0), argInfo.getFloatArg(1), argInfo.getFloatArg(2), argInfo.getFloatArg(3));
            break;
        default:
            break;
    }
}

bool Manage_scenario::intermediate(Execution& execution, arg_info_t& argInfo){
    bool flag = false;
    switch(execution){
        case Execution::CALL_SCENARIO:
            printf("error at Manage_scenario::execute() : CALL_SCENARIOが到達");
            break;
        case Execution::MANUAL:
            break;
        case Execution::STOP:
            break;
        case Execution::TRACE:
            this->lineTrace.trace(argInfo.getFloatArg(0), argInfo.getFloatArg(1), argInfo.getFloatArg(2), argInfo.getFloatArg(3));
            break;
        default:
            break;
    }
    return flag;
}

void Manage_scenario::end(Execution& execution, arg_info_t& argInfo){
    switch(execution){
        default:
            break;
    }
}