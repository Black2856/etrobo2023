#include "RGBtoHSV.h"
#include <algorithm>
#include <math.h>

RGBtoHSV::RGBtoHSV():
    device(deviceInOut::getInstance()){}

void RGBtoHSV::update() {
    device.colorSensor.getRawColor(rgb);
    max = std::max(std::max(rgb.r, rgb.g), rgb.b);
    min = std::min(std::min(rgb.r, rgb.g), rgb.b);

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
    return fmodf((tmp + 360), 360);
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
