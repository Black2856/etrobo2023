/*
 * クラス名:RGBtoHSV
 * 作成日:2023/04/21
 * 作成者:杉本
 */
#ifndef RGB_TO_HSV_H
#define RGB_TO_HSV_H

#include "DeviceInOut.h"
#include "unit.h"

class RGBtoHSV {  // <1>
public:
    explicit RGBtoHSV();
    void update(rgb_raw_t rgb);
    void update();
    unit::hsv_t getHSV();

private:
    // 色相 0 ~ 360°
    uint16_t getHue();
    // 彩度 0 ~ 100%
    uint16_t getSaturation();
    // 明度 0 ~ 100%
    uint16_t getValue();

    void calcMaxMin(rgb_raw_t rgb);

    DeviceInOut& device;

    rgb_raw_t rgb;
    unit::hsv_t hsv;
    float max, min;
};

#endif  // RGB_TO_HSV_H