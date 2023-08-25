/*
 * クラス名:JudgeColor
 * 作成日:2023/08/25
 * 作成者:船田
 */
#include "JudgeColor.h"

JudgeColor::JudgeColor():
    device(DeviceInOut::getInstance()){}

bool JudgeColor::j(unit::color_t color){
    return color == this->getColor();
}

unit::color_t JudgeColor::getColor(){
    this->rgb2hsv.update();
    unit::hsv_t hsv = this->rgb2hsv.getHSV();
    
    if((0 <= hsv.h && hsv.h <= 0) && (0 <= hsv.s && hsv.s <= 0) && (0 <= hsv.v && hsv.v <= 0)){
        return unit::color_t::BLACK;

    }else if((0 <= hsv.h && hsv.h <= 0) && (0 <= hsv.s && hsv.s <= 0) && (0 <= hsv.v && hsv.v <= 0)){
        return unit::color_t::WHITE;

    }else if((0 <= hsv.h && hsv.h <= 0) && (0 <= hsv.s && hsv.s <= 0) && (0 <= hsv.v && hsv.v <= 0)){
        return unit::color_t::YELLOW;

    }else if((0 <= hsv.h && hsv.h <= 0) && (0 <= hsv.s && hsv.s <= 0) && (0 <= hsv.v && hsv.v <= 0)){
        return unit::color_t::RED;

    }else if((0 <= hsv.h && hsv.h <= 0) && (0 <= hsv.s && hsv.s <= 0) && (0 <= hsv.v && hsv.v <= 0)){
        return unit::color_t::GREEN;
        
    }else if((0 <= hsv.h && hsv.h <= 0) && (0 <= hsv.s && hsv.s <= 0) && (0 <= hsv.v && hsv.v <= 0)){
        return unit::color_t::BLUE;
    }

    return unit::color_t::WHITE;
}