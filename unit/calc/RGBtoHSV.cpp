/*
 * クラス名:RGBtoHSV
 * 作成日：2023/04/21
 * 作成者:杉本
 * 修正日:2023/05/19
 * 修正者:杉本
 * ver:1.1.0
 */
#include "RGBtoHSV.h"

RGBtoHSV::RGBtoHSV():
    device(deviceInOut::getInstance()){}

void RGBtoHSV::update() {
    rgb = device.color_getRawColor();

// 最小値と最大値を計算
    max = rgb.r;
    min = rgb.r;

    if(rgb.g > max) {
        max = rgb.g;
    }
    if(rgb.g < min) {
        min = rgb.g;
    }

    if(rgb.b > max) {
        max = rgb.b;
    }
    if(rgb.b < min) {
        min = rgb.b;
    }

    hsv.h = getHue();
    hsv.s = getSaturation();
    hsv.v = getValue();
}

uint16_t RGBtoHSV::getHue() {
    float tmp;
    // すべて同値だったら
    if (max == min) {
        return 0;

    // 赤が最大値だったら
    } else if (max == rgb.r) {
        tmp = 60 * ((rgb.g-rgb.b) / (max-min));

    // 緑が最大値だったら
    } else if (max == rgb.g) {
        tmp = 60 * ((rgb.b-rgb.r) / (max-min)) + 120;

    // 青が最大値だったら
    } else {
        tmp = 60 * ((rgb.r-rgb.g) / (max-min)) + 240;
    }
    // マイナス値になることもあるため、0～360の範囲に収める
    if (tmp < 0) {
        return tmp + 360;
    } else {
        return tmp;
    }
}

uint16_t RGBtoHSV::getSaturation() {
    if (max == min) {
        return 0;
    } else {
        return ((max - min) / max) * 100;
    }
}

uint16_t RGBtoHSV::getValue() {
    return (max / 255) * 100;
}
