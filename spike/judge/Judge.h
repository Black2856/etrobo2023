/*
 * クラス名:Judge
 * 作成日:2023/06/07
 * 作成者:杉本
 */
#ifndef JUDGE_H
#define JUDGE_H

#include "JudgeAngle.h"
#include "JudgeMileage.h"
#include "JudgeSonar.h"
#include "JudgeTime.h"

class Judge {
public:
    // インスタンス取得
    static Judge& getInstance();

    // 各種インスタンス
    JudgeAngle   angle;
    JudgeMileage mileage;
    JudgeSonar   sonar;
    JudgeTime    time;

private:

    Judge(); // プライベートコンストラクタ
    static Judge* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Judge(Judge const&);
    void operator=(Judge const&);
};

#endif  // JUDGE_H