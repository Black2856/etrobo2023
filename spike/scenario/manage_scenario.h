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
#include "unit.h"

#include "LineTrace.h"

#include <cstring>
#include <list>

class Manage_scenario{
public:
    void add(Manage_scene manageScene); //scene管理クラスを追加する
    void update(); //scene管理クラス(シナリオデータ)から各シーンへのコンパイル
    bool execute(); //return : sceneのIdxが最後かどうか

private:
    JudgeMileage mileage;
    JudgeSonar sonar;
    JudgeTime time;
    JudgeAngle angle;
    unit::judge judge = {&mileage, &sonar, &time, &angle};

    std::list<Scene> compileScene;
    std::list<Manage_scene> scenarioList;
    uint16_t executeIdx = 0;
    //動作のインスタンス
    LineTrace lineTrace;

    void addScene(Manage_scene& manageScene); //１つシーン管理クラスをコンパイルする
    Manage_scene* findScenario(const char* name); //シーン管理クラスから特定の名前のシナリオを取得する
};

#endif