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
#include <vector>
#include <string>

class Manage_scenario{
public:
    void add(Manage_scene manageScene); //scene管理クラスを追加する
    void update(); //scene管理クラス(シナリオデータ)から各シーンへのコンパイル
    bool execute(); //return : sceneのIdxが最後かどうか

private:
    std::vector<Scene&> compileScene;
    std::vector<Manage_scene> scenarioList;
    uint16_t executeIdx = 0;
    
    void addScene(const Manage_scene& manageScene); //１つシーン管理クラスをコンパイルする
    Manage_scene& findScenario(const std::string name); //シーン管理クラスから特定の名前のシナリオを取得する
};

#endif