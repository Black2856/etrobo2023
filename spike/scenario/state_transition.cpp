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
        case 0: func = [](Judge& j) {return j.time.j(500 * 1000);}; break;
        case 1: func = [](Judge& j) {return j.ret.j(true) and j.time.j(3000 * 1000) or j.color.j(unit::color_t::COLOR);}; break;
        case 2: func = [](Judge& j) {return j.time.j(200 * 1000);}; break;
        case 3: func = [](Judge& j) {return j.ret.j(true) and j.time.j(2000 * 1000);}; break;
        case 4: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 5: func = [](Judge& j) {return j.button.j(4, true) or j.touch.j(true);}; break;
    //#</func_list>
        default: return true;
    }
    
    return func(j);
}