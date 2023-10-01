/*
 * 作成日:2023/10/1
 * 作成者:船田
 */

#include "custom_scenario.h"

void Custom_scenario::mainProcess(Manage_scenario* manage_scenario){
    //ファイル読取処理
    readSig.main();

    // トレジャーエリアの走行経路
    if (generalData.getIsData(0) == true && this->isMakeTA == false){
        this->makeTreasureArea(manage_scenario, generalData.getRunRoute());
    }
}

void Custom_scenario::makeTreasureArea(Manage_scenario* manage_scenario, const std::list<int>& runRoute){
    // 各要素からシナリオへ変換
    for (int id : runRoute) {
        if (id == 0){// 直進 
            this->block.makeCALL_SCENARIO("straight");
        }else if(id == 1){//右回転
            this->block.makeCALL_SCENARIO("right");
        }else if(id == 2){//左回転
            this->block.makeCALL_SCENARIO("left");
        }else{
            printf("error makeTreasureArea:wrong runRoute");
        }
    }

    // シナリオ管理の再コンパイル
    manage_scenario->add(this->block);
    manage_scenario->update();
    this->isMakeTA = true;
}