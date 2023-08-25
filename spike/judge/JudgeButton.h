/*
 * クラス名:JudgeButton
 * 作成日:2023/08/25
 * 作成者:船田
 */
#ifndef JUDGE_BUTTON_H
#define JUDGE_BUTTON_H

#include "DeviceInOut.h"

class JudgeButton {
public:
    JudgeButton();
    bool j(int button, bool flag);
private:
    DeviceInOut& device;
};

#endif  // JUDGE_BUTTON_H