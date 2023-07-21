/*
 * 2023/07/10
 * hunada
 */
#include "state_transition.h"

StateTransition::StateTransition(){
}

bool StateTransition::judge(int idx){
    FuncList funcList;
    std::function<bool(Judge& j)> func;

    switch(idx):
    //#<func_list>
        case 0: func = [](Judge& j) {return j.mileage.j(1000);}; break;
        case 1: func = [](Judge& j) {return (j.angle.j(90) and j.sonar.j(10));}; break;
        case 2: func = [](Judge& j) {return j.time.j(2500 * 1000);}; break;
        case 3: func = [](Judge& j) {return j.mileage.j(1500);}; break;
        case 4: func = [](Judge& j) {return j.time.j(1000 * 1000);}; break;
        case 5: func = [](Judge& j) {return j.time.j(3000 * 1000);}; break;
        case 6: func = [](Judge& j) {return j.time.j(1500 * 1000);}; break;
    //#</func_list>
        default: return true;
    return func(j);
}