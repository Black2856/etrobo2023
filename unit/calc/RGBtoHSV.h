#ifndef RGB_TO_HSV_H
#define RGB_TO_HSV_H

#include "deviceInOut.h"

// h, 色相, 0 ~ 360
// s, 彩度, 0 ~ 100
// v, 明度, 0 ~ 100
struct hsv_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
};

class RGBtoHSV {  // <1>
public:
    explicit RGBtoHSV();
    void update();
    hsv_t getHSV();

private:
    // 色相 0 ~ 360°
    uint16_t getHue();
    // 彩度 0 ~ 100%
    uint16_t getSaturation();
    // 明度 0 ~ 100%
    uint16_t getValue();

    deviceInOut& device;

    rgb_raw_t rgb;
    hsv_t hsv;
    float max, min;
};

#endif  // RGB_TO_HSV_H