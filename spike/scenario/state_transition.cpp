/*
 * 2023/07/10
 * hunada
 */
#include "state_transition.h"

StateTransition::StateTransition(){
}

bool StateTransition::judge(int idx){
    //If no condition is set
    if(idx == -1){
        return true;
    }

    std::function<bool(Judge& j)> func;

    switch(idx){
    //#<func_list>
        case 0: func = [](Judge& j) {return j.angle.j(10);}; break;
        case 1: func = [](Judge& j) {return j.angle.j(-280);}; break;
        case 2: func = [](Judge& j) {return j.time.j(1000 * 1000);}; break;
        case 3: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 4: func = [](Judge& j) {return j.time.j(1000 * 1000);}; break;
        case 5: func = [](Judge& j) {return j.touch.j(true);}; break;
        case 6: func = [](Judge& j) {return j.time.j(2000 * 1000);}; break;
        case 7: func = [](Judge& j) {return j.time.j(3000 * 1000);}; break;
        case 8: func = [](Judge& j) {return j.time.j(2000 * 1000);}; break;
        case 9: func = [](Judge& j) {return j.angle.j(90);}; break;
        case 10: func = [](Judge& j) {return j.time.j(1000 * 1000);}; break;
        case 11: func = [](Judge& j) {return j.time.j(7000 * 1000);}; break;
        case 12: func = [](Judge& j) {return j.angle.j(360);}; break;
        case 13: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 14: func = [](Judge& j) {return j.time.j(30000 * 1000);}; break;
    //#</func_list>
        default: return true;
    }
    
    return func(j);
}