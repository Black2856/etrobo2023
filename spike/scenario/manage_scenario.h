/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef MANAGE_SCENARIO_H
#define MANAGE_SCENARIO_H

#include "manage_scene.h"
#include "scene.h"
#include "execution.h"
#include "arg_info.h"
#include "Judge.h"
#include "state_transition.h"
#include "unit.h"

#include "LineTrace.h"
#include "Stop.h"
#include "Manual.h"
#include "OnLineMove.h"
#include "Calibration.h"

#include <cstring>
#include <list>

class Manage_scenario{
public:
    void add(Manage_scene manageScene); //scene管理クラスを追加する
    void update(); //scene管理クラス(シナリオデータ)から各シーンへのコンパイル
    bool execute(); //return : sceneのIdxが最後かどうか

    void first(Execution& execution, arg_info_t& argInfo); //シーン遷移時に動作させるプログラム
    bool intermediate(Execution& execution, arg_info_t& argInfo); //シーン中に動作させるプログラム
    void end(Execution& execution, arg_info_t& argInfo); //シーン終了時に動作させるプログラム
    void backGround(); //同期的にバックグラウンドで動作させるプログラム(

private:
    StateTransition stateTransition;
    std::list<Scene> compileScene;
    std::list<Manage_scene> scenarioList;
    uint16_t executeIdx = 0;
    bool isFirst = true;
    
    //動作のインスタンス
    LineTrace lineTrace;
    Stop stop;
    Manual manual;
    OnLineMove onLineMove;
    Calibration calibration;

    void addScene(Manage_scene& manageScene); //１つシーン管理クラスをコンパイルする
    Manage_scene* findScenario(const char* name); //シーン管理クラスから特定の名前のシナリオを取得する
};

#endif