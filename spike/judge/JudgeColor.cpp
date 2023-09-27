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

    // テスト表示
    //printf("<%d, %d, %d>", hsv.h, hsv.s, hsv.v);

    unit::calibration_t color = this->generalData.getColor();

    if((0 <= hsv.s && hsv.s <= 50) && (0 <= hsv.v && hsv.v <= color.avg)){
        return unit::color_t::BLACK;

    }else if((0 <= hsv.s && hsv.s <= 50) && (color.avg <= hsv.v && hsv.v <= 100)){
        return unit::color_t::WHITE;

    }else {
        return unit::color_t::COLOR;
    }
    /*
    if((0 <= hsv.h && hsv.h <= 360) && (5 <= hsv.s && hsv.s <= 60) && (0 <= hsv.v && hsv.v <= 30)){
        return unit::color_t::BLACK;

    }else if((0 <= hsv.h && hsv.h <= 360) && (0 <= hsv.s && hsv.s <= 25) && (50 <= hsv.v && hsv.v <= 100)){
        return unit::color_t::WHITE;

    }else if((195 <= hsv.h && hsv.h <= 235) && (60 <= hsv.s && hsv.s <= 100) && (45 <= hsv.v && hsv.v <= 100)){
        return unit::color_t::BLUE;

    }else if((35 <= hsv.h && hsv.h <= 75) && (60 <= hsv.s && hsv.s <= 100) && (60 <= hsv.v && hsv.v <= 100)){
        return unit::color_t::YELLOW;

    }else if((0 <= hsv.h && hsv.h <= 30) && (50 <= hsv.s && hsv.s <= 100) && (60 <= hsv.v && hsv.v <= 100)){
        return unit::color_t::RED;

    }else if((120 <= hsv.h && hsv.h <= 160) && (50 <= hsv.s && hsv.s <= 100) && (45 <= hsv.v && hsv.v <= 100)){
        return unit::color_t::GREEN;
    }
    */

    return unit::color_t::WHITE;
}