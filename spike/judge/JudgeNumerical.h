/*
 * クラス名:JudgeNumerical
 * 作成日:2023/05/26
 * 作成者:杉本
 */
#ifndef JUDGE_NUMERICAL_H
#define JUDGE_NUMERICAL_H

class JudgeNumerical {
public:
    JudgeNumerical();

    void stop();
    bool j(float target);

    float getTarget() const;
    float getPreviousValue() const;
    bool isStarted() const;

protected:
    // 派生クラス毎に計測に使用する値を返却する
    virtual float getValue() const = 0;
    virtual bool  isTargetReached();

    float getStartNumerical() const;
    float previousValue;
private:
    void setTarget(float target);
    void start();

    float mTarget;         // 目標値
    float mStartNumerical; // 計測開始時数値
    bool  mStartFlg;
};

#endif  // JUDGE_NUMERICAL_H