#ifndef UNIT_H
#define UNIT_H

#include "ev3api.h"
#include <list>

namespace unit {

    enum color_t {
        RED,
        BLUE,
        YELLOW,
        GREEN,
        WHITE,
        BLACK,
    };

    // h, 色相, 0 ~ 360
    // s, 彩度, 0 ~ 100
    // v, 明度, 0 ~ 100
    struct hsv_t {
        uint16_t h;
        uint16_t s;
        uint16_t v;
    };

    struct pid_t {
        float kp;
        float ki;
        float kd;
    };

    struct normality_t {
        bool sonar;
        bool touch;
        bool gyro;
        bool color;
        bool left_wheel;
        bool right_wheel;
    };

    struct calibration_t {
        int max;
        int min;
        int avg;
    };

    //unit::getElementAt(list<any>, idx); listの要素idxを取り出す
    template<typename T>
    T getList(const std::list<T>& myList, size_t index) {
        auto it = myList.begin();
        std::advance(it, index);
        return *it;
    }
}

#endif // UNIT_H