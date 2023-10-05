/*
 * 作成日:2023/06/26
 * 作成者:船田
 */

#include "manage_scenario.h"

void Manage_scenario::add(Manage_scene manageScene){
    // 重複するシナリオは上書き
    const char* removeName = manageScene.getName();
    this->remove(removeName);
    this->scenarioList.push_back(manageScene);
}

void Manage_scenario::remove(const char* name){

    for (auto it = scenarioList.begin(); it != scenarioList.end(); ) {
        //printf("%s, %s\n", it->getName(), name);
        if (std::strcmp(it->getName(), name) == 0) {
            it = scenarioList.erase(it);
        } else {
            ++it;
        }
    }
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

    //バックグラウンド動作の呼び出し処理
    this->backGround();

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

        j.allReset();
        
        this->isFirst = true;
        this->executeIdx ++;
        printf("*遷移 => %d*\n", this->executeIdx);
    }

    //終端かどうか
    if(this->compileScene.size() - 1 < this->executeIdx){
        printf("*終了*\n");
        return true; //終了
    }else{
        return false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//シーン遷移初回動作(1回のみ)
void Manage_scenario::first(Execution& execution, arg_info_t& argInfo){
    switch(execution){
        case Execution::STOP:
            this->stop.first(argInfo.getFloatArg(0));
            break;
        case Execution::TRACE:
            this->lineTrace.first(argInfo.getFloatArg(0), argInfo.getFloatArg(1), argInfo.getFloatArg(2), argInfo.getFloatArg(3), argInfo.getFloatArg(4));
            break;
        case Execution::MANUAL:
            this->manual.first((manual::RunType)int(argInfo.getFloatArg(0)), argInfo.getFloatArg(1), argInfo.getFloatArg(2));
            break;
        case Execution::MANUAL_PID:
            this->manualPID.first((manualPID::RunType)int(argInfo.getFloatArg(0)), argInfo.getFloatArg(1), argInfo.getFloatArg(2));
            break;
        case Execution::CALIBRATION:
            this->calibration.first(argInfo.getStrArg(0));
            break;
        case Execution::TAKE_PHOTO:
            this->takePhoto.first(argInfo.getFloatArg(0));
            break;
        default:
            break;
    }
}
//シーン動作(常時)
bool Manage_scenario::intermediate(Execution& execution, arg_info_t& argInfo){
    bool flag = false;
    switch(execution){
        case Execution::CALL_SCENARIO:
            printf("error at Manage_scenario::execute() : CALL_SCENARIOが到達");
            break;
        case Execution::STOP:
            flag = this->stop.execute();
            break;
        case Execution::MANUAL:
            this->manual.execute();
            break;
        case Execution::TRACE:
            this->lineTrace.trace();
            break;
        case Execution::MANUAL_PID:
            flag = this->manualPID.execute();
            break;
        case Execution::TAKE_PHOTO:
            flag = this->takePhoto.execute();
            break;
        default:
            break;
    }
    return flag;
}
//シーン終了動作(1回のみ)
void Manage_scenario::end(Execution& execution, arg_info_t& argInfo){
    switch(execution){
        default:
            break;
    }
}

//バックグラウンド動作
void Manage_scenario::backGround(){
    if(this->calibration.getState() == true){
        this->calibration.execute();
    }
}