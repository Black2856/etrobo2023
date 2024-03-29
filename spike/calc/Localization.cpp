/*
 * クラス名:Localization
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#include "Localization.h"
#include "setting.h"

Localization* Localization::instance = NULL;

Localization::Localization():
    device(DeviceInOut::getInstance()) {
        distance  = 0;
        direction = 0;
        //モータ角度の過去値に現在値を代入
        pre_angleL = device.LWheel_getCount();
        pre_angleR = device.RWheel_getCount();
    }

Localization& Localization::getInstance() {
    if (!instance) {
        instance = new Localization();
    }
    return *instance;
}

/* 更新 */
void Localization::update() {
    distance  += calcDistance();
    direction += calcDirection();
}

/* 走行距離を取得（mm） */
float Localization::getDistance() {
    this->update(); //同時期のタスクで記録パッケージに存在したらそこから取得
    return distance;
}

/* 車体角度を取得（deg） */
float Localization::getDirection() {
    this->update(); //同時期のタスクで記録パッケージに存在したらそこから取得
    return direction;
}

float Localization::getDifferenceCount() {
    this->update();
    float differenceL = this->distanceL - this->offsetL;
    float differenceR = this->distanceR - this->offsetR;
    return differenceL - differenceR;
}

void Localization::resetDifferenceCount() {
    this->update();
    this->offsetL =  this->distanceL;
    this->offsetR =  this->distanceR;
}

float Localization::calcDistance() {
    //左モータ回転角度の現在値
    float cur_angleL = device.LWheel_getCount();
    //右モータ回転角度の現在値
    float cur_angleR = device.RWheel_getCount();

    // 今回の走行距離L,R = ((円周率 * タイヤの直径) / 360) * (モータ角度過去値　- モータ角度現在値)
    distanceL = ((PI * TIRE_DIAMETER) / 360) * (cur_angleL - pre_angleL);  // 左モータ距離
    distanceR = ((PI * TIRE_DIAMETER) / 360) * (cur_angleR - pre_angleR);  // 右モータ距離

    //モータの回転角度の過去値を更新
    pre_angleL = cur_angleL;
    pre_angleR = cur_angleR;

    // 左右タイヤの走行距離の平均を返却
    return (distanceL + distanceR) / 2; 
}

float Localization::calcDirection() {
    //(360 / (2 * 円周率 * 車体トレッド幅)) * (右進行距離 - 左進行距離)
    return (360.0 / (2.0 * PI * TREAD)) * (distanceL - distanceR);
}