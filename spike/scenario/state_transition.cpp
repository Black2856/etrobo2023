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
        case 1: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 2: func = [](Judge& j) {return j.ret.j(true) and j.time.j(1500 * 1000);}; break;
        case 3: func = [](Judge& j) {return j.time.j(200 * 1000);}; break;
        case 4: func = [](Judge& j) {return j.ret.j(true) and j.time.j(1500 * 1000);}; break;
        case 5: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 6: func = [](Judge& j) {return j.button.j(4, true) or j.touch.j(true);}; break;
        case 7: func = [](Judge& j) {return j.mileage.j(2700);}; break;
        case 8: func = [](Judge& j) {return j.mileage.j(600);}; break;
        case 9: func = [](Judge& j) {return j.mileage.j(1600);}; break;
        case 10: func = [](Judge& j) {return j.mileage.j(550);}; break;
        case 11: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 12: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 13: func = [](Judge& j) {return j.mileage.j(1300);}; break;
        case 14: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 15: func = [](Judge& j) {return j.mileage.j(700);}; break;
        case 16: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 17: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 18: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 19: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 20: func = [](Judge& j) {return j.mileage.j(50);}; break;
        case 21: func = [](Judge& j) {return j.mileage.j(1000);}; break;
        case 22: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 23: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 24: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 25: func = [](Judge& j) {return j.time.j(5000*1000);}; break;
        case 26: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 27: func = [](Judge& j) {return j.mileage.j(50);}; break;
        case 28: func = [](Judge& j) {return j.mileage.j(1000);}; break;
        case 29: func = [](Judge& j) {return j.mileage.j(850);}; break;
        case 30: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 31: func = [](Judge& j) {return j.mileage.j(100);}; break;
        case 32: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 33: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 34: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 35: func = [](Judge& j) {return j.mileage.j(50);}; break;
        case 36: func = [](Judge& j) {return j.mileage.j(1500);}; break;
        case 37: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 38: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 39: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 40: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
    //#</func_list>
        default: return true;
    }
    
    return func(j);
}