/*
 * クラス名:JudgeTime
 * 作成日：2023/05/19
 * 作成者:杉本
 * 修正日:
 * 修正者:
 * ver:1.0.0
 */
#ifndef _JUDGETIME_H_
#define _JUDGETIME_H_

#include "DeviceInOut.h"

class JudgeTime {
public:
    explicit JudgeTime();

    bool judge(uint32_t delay);

private:

    void setTime(uint32_t delay);
    void start();
    void stop();
    bool isTimedOut() const;
    bool isStarted() const;

    DeviceInOut& device;

    uint32_t mDelayMs;      // 満期時間
    uint32_t mStartTime;    // 計測開始時間
    uint32_t mTargetTime;   // 計測開始時間 + 満期時間
};

#endif  // _JUDGETIME_H_