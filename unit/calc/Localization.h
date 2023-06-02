/*
 * クラス名:Localization
 * 作成日：2023/05/12
 * 作成者:杉本
 */
#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include "DeviceInOut.h"

// 円周率
#define PI 3.14159265358

class Localization {
public:
    // インスタンス取得
    static Localization& getInstance();

    /* 更新 */
    void update();
    /* 走行距離を取得（mm） */
    float getDistance();
    /* 車体角度を取得（deg） */
    float getDirection();

private:

    Localization(); // プライベートコンストラクタ
    static Localization* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Localization(Localization const&);
    void operator=(Localization const&);

    // 前回計算時から現在までの走行距離を計算
    float calcDistance();
    // 前回計算時から現在までの角度変化を計算
    float calcDirection();

    DeviceInOut& device;

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