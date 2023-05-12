#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include "deviceInOut.h"

// 円周率
#define PI 3.14159265358

class Localization {
public:
    explicit Localization();
    /* 更新 */
    void update();
    /* 走行距離を取得 */
    float getDistance();
    /* 車体角度を取得 */
    float getDirection();

private:
    float calcDistance();
    float calcDirection();

    deviceInOut& device;

    // 各タイヤの走行距離
    float distanceL, distanceR;
    // 車体総走行距離
    float distance;
    // 車体角度
    float direction;
    // 左右モータ回転角度の過去値
    float pre_angleL, pre_angleR;
};

#endif  // _LOCALIZATION_H_