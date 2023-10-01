/*
 * 作成日:2023/10/1
 * 作成者:船田
 */
#ifndef CUSTOM_SCENARIO_H
#define CUSTOM_SCENARIO_H

#include "manage_scenario.h"
#include "manage_scene.h"
#include "GeneralData.h"
#include "ReadSig.h"

#include <list>

class Custom_scenario{
public:
    // manage_scenarioに特殊なシナリオを追加する等の処理
    void mainProcess(Manage_scenario* manage_scenario);

private:
    GeneralData& generalData = GeneralData::getInstance();
    ReadSig readSig;

    void makeTreasureArea(Manage_scenario* manage_scenario, const std::list<int>& runRoute);
    Manage_scene block = Manage_scene("block");
    bool isMakeTA = false;
};

#endif //CUSTOM_SCENARIO_H