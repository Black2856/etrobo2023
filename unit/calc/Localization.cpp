#include "Localization.h"
#include "setting.h"

Localization::Localization():
    device(deviceInOut::getInstance()) {
        distance  = 0;
        direction = 0;
        //モータ角度の過去値に現在値を代入
        pre_angleL = device.leftWheel.getCount();
        pre_angleR = device.rightWheel.getCount();
    }

/* 更新 */
void Localization::update() {
    calcDistance();
    calcDirection();
}

/* 走行距離を取得（mm） */
float Localization::getDistance() {
    return distance;
}

float Localization::getDirection() {
    return direction;
}

float Localization::calcDistance() {
    //左モータ回転角度の現在値
    float cur_angleL = device.leftWheel.getCount();
    //右モータ回転角度の現在値
    float cur_angleR = device.rightWheel.getCount();
    //今回の走行距離
    float dis;

    // 今回の走行距離L,R = ((円周率 * タイヤの直径) / 360) * (モータ角度過去値　- モータ角度現在値)
    distanceL = ((PI * TIRE_DIAMETER) / 360) * (cur_angleL - pre_angleL);  // 左モータ距離
    distanceR = ((PI * TIRE_DIAMETER) / 360) * (cur_angleR - pre_angleR);  // 右モータ距離

    dis = (distanceL + distanceR) / 2; //左右タイヤの走行距離の平均
    distance += dis;

    //モータの回転角度の過去値を更新
    pre_angleL = cur_angleL;
    pre_angleR = cur_angleR;
}

float Localization::calcDirection() {
    //(360 / (2 * 円周率 * 車体トレッド幅)) * (右進行距離 - 左進行距離)
    direction += (360.0 / (2.0 * PI * TREAD)) * (distanceL - distanceR);
}