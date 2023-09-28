/*
 * クラス名:Judge
 * 作成日:2023/06/07
 * 作成者:杉本
 */
#ifndef JUDGE_H
#define JUDGE_H

#include "JudgeBrightness.h"
#include "JudgeAngle.h"
#include "JudgeAngleMinifig.h"
#include "JudgeMileage.h"
#include "JudgeSonar.h"
#include "JudgeTime.h"
#include "JudgeReturn.h"
#include "JudgeTouch.h"
#include "JudgeColor.h"
#include "JudgeButton.h"

class Judge {
public:
    // インスタンス取得
    static Judge& getInstance();
    void allReset(); //全ての計測をstopする

    // 各種インスタンス
    JudgeBrightness   brightness;
    JudgeAngle   angle;
    JudgeAngleMinifig   angleMinifig;
    JudgeMileage mileage;
    JudgeSonar   sonar;
    JudgeTime    time;
    JudgeReturn  ret;
    JudgeTouch   touch;
    JudgeButton  button;
    JudgeColor   color;

private:
    Judge(); // プライベートコンストラクタ
    static Judge* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Judge(Judge const&);
    void operator=(Judge const&);
};

#endif  // JUDGE_H