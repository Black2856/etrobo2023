/*
 * クラス名:JudgeNumerical
 * 作成日：2023/05/26
 * 作成者:杉本
 */
#ifndef _JUDGE_NUMERICAL_H_
#define _JUDGE_NUMERICAL_H_

class JudgeNumerical {
public:
    JudgeNumerical();

    bool judge(float interval);

private:

            void setNumerical(float interval);
    virtual void start() = 0;
            void stop();
    virtual bool isTargetReached() const = 0;
            bool isStarted() const;

    float mInterval;         // 間隔
    float mStartNumerical;   // 計測開始時数値
    float mTargetNumerical;  // 目標値
};

#endif  // _JUDGE_NUMERICAL_H_