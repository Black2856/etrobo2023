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
        case 7: func = [](Judge& j) {return j.mileage.j(100);}; break;
        case 8: func = [](Judge& j) {return j.mileage.j(550);}; break;
        case 9: func = [](Judge& j) {return j.mileage.j(100);}; break;
        case 10: func = [](Judge& j) {return j.mileage.j(1400);}; break;
        case 11: func = [](Judge& j) {return j.mileage.j(130);}; break;
        case 12: func = [](Judge& j) {return j.mileage.j(490);}; break;
        case 13: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 14: func = [](Judge& j) {return j.mileage.j(1280);}; break;
        case 15: func = [](Judge& j) {return j.mileage.j(130);}; break;
        case 16: func = [](Judge& j) {return j.mileage.j(130);}; break;
        case 17: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 18: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 19: func = [](Judge& j) {return j.ret.j(true) or j.time.j(7000* 1000);}; break;
        case 20: func = [](Judge& j) {return j.time.j(2000*1000);}; break;
        case 21: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 22: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 23: func = [](Judge& j) {return j.angleMinifig.j(1);}; break;
        case 24: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 25: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 26: func = [](Judge& j) {return j.ret.j(true) or j.time.j(7000* 1000);}; break;
        case 27: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 28: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 29: func = [](Judge& j) {return j.angleMinifig.j(2);}; break;
        case 30: func = [](Judge& j) {return j.mileage.j(50);}; break;
        case 31: func = [](Judge& j) {return j.brightness.j(15);}; break;
        case 32: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 33: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 34: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 35: func = [](Judge& j) {return j.mileage.j(150);}; break;
        case 36: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 37: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 38: func = [](Judge& j) {return j.ret.j(true) or j.time.j(7000* 1000);}; break;
        case 39: func = [](Judge& j) {return j.time.j(2000*1000);}; break;
        case 40: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 41: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 42: func = [](Judge& j) {return j.angleMinifig.j(-1);}; break;
        case 43: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 44: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 45: func = [](Judge& j) {return j.ret.j(true) or j.time.j(7000* 1000);}; break;
        case 46: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 47: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 48: func = [](Judge& j) {return j.angleMinifig.j(-2);}; break;
        case 49: func = [](Judge& j) {return j.mileage.j(400);}; break;
        case 50: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 51: func = [](Judge& j) {return j.mileage.j(40) and j.brightness.j(20);}; break;
        case 52: func = [](Judge& j) {return j.time.j(500*1000);}; break;
        case 53: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 54: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 55: func = [](Judge& j) {return j.mileage.j(400);}; break;
        case 56: func = [](Judge& j) {return j.time.j(100*1000);}; break;
        case 57: func = [](Judge& j) {return j.time.j(1000*1000);}; break;
        case 58: func = [](Judge& j) {return j.mileage.j(450);}; break;
        case 59: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 60: func = [](Judge& j) {return j.ret.j(true) and j.time.j(400 * 1000);}; break;
        case 61: func = [](Judge& j) {return j.ret.j(true) and j.time.j(400 * 1000);}; break;
        case 62: func = [](Judge& j) {return j.time.j(50 * 1000);}; break;
        case 63: func = [](Judge& j) {return j.ret.j(true) and j.time.j(400 * 1000);}; break;
        case 64: func = [](Judge& j) {return j.ret.j(true) and j.time.j(400 * 1000);}; break;
        case 65: func = [](Judge& j) {return j.time.j(50 * 1000);}; break;
        case 66: func = [](Judge& j) {return j.mileage.j(600);}; break;
        case 67: func = [](Judge& j) {return j.mileage.j(850);}; break;
        case 68: func = [](Judge& j) {return j.mileage.j(1350);}; break;
        case 69: func = [](Judge& j) {return j.brightness.j(90) and j.time.j(200 * 1000);}; break;
        case 70: func = [](Judge& j) {return j.ret.j(true) and j.time.j(200*1000);}; break;
        case 71: func = [](Judge& j) {return j.time.j(700*1000);}; break;
        case 72: func = [](Judge& j) {return j.ret.j(true) and j.time.j(500*1000);}; break;
        case 73: func = [](Judge& j) {return j.time.j(700*1000);}; break;
        case 74: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 75: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 76: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 77: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 78: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 79: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 80: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 81: func = [](Judge& j) {return j.ret.j(true) and j.time.j(300*1000);}; break;
        case 82: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 83: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 84: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 85: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 86: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 87: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 88: func = [](Judge& j) {return j.ret.j(true) and j.time.j(300*1000);}; break;
        case 89: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
        case 90: func = [](Judge& j) {return j.mileage.j(550);}; break;
        case 91: func = [](Judge& j) {return j.ret.j(true);}; break;
        case 92: func = [](Judge& j) {return j.time.j(500 * 1000);}; break;
        case 93: func = [](Judge& j) {return j.ret.j(true) and j.time.j(300*1000);}; break;
        case 94: func = [](Judge& j) {return j.ret.j(true) and j.time.j(300*1000);}; break;
        case 95: func = [](Judge& j) {return j.time.j(500 * 1000);}; break;
        case 96: func = [](Judge& j) {return j.mileage.j(300);}; break;
        case 97: func = [](Judge& j) {return j.brightness.j(60) and j.mileage.j(300);}; break;
        case 98: func = [](Judge& j) {return j.time.j(100 * 1000);}; break;
    //#</func_list>
        default: return true;
    }
    
    return func(j);
}