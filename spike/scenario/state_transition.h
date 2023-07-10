/*
 * 作成日:2023/07/10
 * 作成者:船田
 */
#ifndef state_transition_H
#define state_transition_H

#include "unit.h"
#include "Judge.h"
#include "func_list.h"
#include <functional>

class StateTransition{
public:
    StateTransition();
    bool judge(int idx);

private:
    Judge& j = Judge::getInstance();
};

#endif