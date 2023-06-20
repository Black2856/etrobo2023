/*
 * クラス名:JudgeNumerical
 * 作成日：2023/05/26
 * 作成者:杉本
 */
#ifndef JUDGE_NUMERICAL_H
#define JUDGE_NUMERICAL_H

class JudgeNumerical {
public:
    JudgeNumerical();

    bool judge(float target);

protected:
    // 派生クラス毎に計測に使用する値を返却する
    virtual float getValue() const = 0;
    virtual bool  isTargetReached() const;

    float getTarget() const;
    float getStartNumerical() const;

private:
    void setTarget(float target);
    void start();
    void stop();
    bool isStarted() const;

    float mTarget;         // 目標値
    float mStartNumerical; // 計測開始時数値
    bool  mStartFlg
};

#endif  // JUDGE_NUMERICAL_H