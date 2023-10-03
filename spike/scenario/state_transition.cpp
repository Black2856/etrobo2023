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
        case 1: func = [](Judge& j) {return j.ret.j(true) and j.time.j(1500 * 1000);}; break;
        case 2: func = [](Judge& j) {return j.time.j(200 * 1000);}; break;
        case 3: func = [](Judge& j) {return j.ret.j(true) and j.time.j(1500 * 1000);}; break;
        case 4: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 5: func = [](Judge& j) {return j.button.j(4, true) or j.touch.j(true);}; break;
        case 6: func = [](Judge& j) {return j.mileage.j(2700);}; break;
        case 7: func = [](Judge& j) {return j.mileage.j(600);}; break;
        case 8: func = [](Judge& j) {return j.mileage.j(1600);}; break;
        case 9: func = [](Judge& j) {return j.mileage.j(550);}; break;
        case 10: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 11: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 12: func = [](Judge& j) {return j.mileage.j(1300);}; break;
        case 13: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 14: func = [](Judge& j) {return j.mileage.j(500);}; break;
        case 15: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 16: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 17: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 18: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 19: func = [](Judge& j) {return j.time.j(4000*1000);}; break;
        case 20: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 21: func = [](Judge& j) {return j.angleMinifig.j(1);}; break;
        case 22: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 23: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 24: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 25: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 26: func = [](Judge& j) {return j.time.j(4000*1000);}; break;
        case 27: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 28: func = [](Judge& j) {return j.angleMinifig.j(2);}; break;
        case 29: func = [](Judge& j) {return j.mileage.j(600);}; break;
        case 30: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 31: func = [](Judge& j) {return j.mileage.j(300);}; break;
        case 32: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 33: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 34: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 35: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 36: func = [](Judge& j) {return j.time.j(4000*1000);}; break;
        case 37: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 38: func = [](Judge& j) {return j.angleMinifig.j(-1);}; break;
        case 39: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 40: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 41: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 42: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 43: func = [](Judge& j) {return j.time.j(4000*1000);}; break;
        case 44: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 45: func = [](Judge& j) {return j.angleMinifig.j(-2);}; break;
        case 46: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 47: func = [](Judge& j) {return j.mileage.j(300);}; break;
        case 48: func = [](Judge& j) {return j.mileage.j(1000);}; break;
        case 49: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 50: func = [](Judge& j) {return j.mileage.j(1000);}; break;
        case 51: func = [](Judge& j) {return j.mileage.j(1000);}; break;
        case 52: func = [](Judge& j) {return j.mileage.j(400) and j.brightness.j(80);}; break;
        case 53: func = [](Judge& j) {return j.time.j(100*1000);}; break;
        case 54: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 55: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 56: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 57: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 58: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 59: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 60: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 61: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 62: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 63: func = [](Judge& j) {return j.ret.j(true) and j.brightness.j(80);}; break;
        case 64: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
    //#</func_list>
        default: return true;
    }
    
    return func(j);
}