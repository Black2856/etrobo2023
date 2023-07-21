/*
 * クラス名:JudgeTouch
 * 作成日:2023/07/21
 * 作成者:松尾
 */
#ifndef JUDGE_TOUCH_H
#define JUDGE_TOUCH_H

#include "DeviceInOut.h"

class JudgeTouch {
public:
    JudgeTouch();
    bool j(bool flag);
private:
    DeviceInOut& device;
};

#endif  // JUDGE_TOUCH_H