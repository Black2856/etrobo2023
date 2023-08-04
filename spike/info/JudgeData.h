/*
 * クラス名:JudgeData
 * 作成日:2023/08/04
 * 作成者:船田
 */

#ifndef JUDGE_DATA_H
#define JUDGE_DATA_H

#include "Judge.h"

//判定の値(float) {計測中か, 現在値, 目標値, 割合}
struct judgeNumerical_t {
    
    bool isStarted = false;
    float now = 0;
    float target = 0;
    float rate = 0;
};

struct judgeValue_t{
    judgeNumerical_t angle;
    judgeNumerical_t mileage;
    judgeNumerical_t sonar;
    judgeNumerical_t time; 
};

//Judgeクラスの判定値を取得できるクラス
class JudgeData {
public:
    static JudgeData& getInstance();

    judgeValue_t getJudgeValue();
    judgeNumerical_t getMostReached(); //最も進行度の高い値を返す

private:
    judgeValue_t judgeValue;
    Judge& j = Judge::getInstance();

    JudgeData(); // プライベートコンストラクタ
    static JudgeData* instance; // シングルトンオブジェクトへのポインタ
    // コピーおよび代入演算子は禁止
    JudgeData(JudgeData const&);
    void operator=(JudgeData const&);
};

#endif