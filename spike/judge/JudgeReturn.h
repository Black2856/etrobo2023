/*
 * クラス名:JudgeReturn
 * 作成日:2023/07/21
 * 作成者:船田
 */
#ifndef JUDGE_RETURN_H
#define JUDGE_RETURN_H

#include "DeviceInOut.h"

class JudgeReturn{
public:
    JudgeReturn();
    bool j(bool flag);
    void setFlag(bool flag);

private:
    bool flag;
    DeviceInOut& device;
};

#endif  // JUDGE_RETURN_H