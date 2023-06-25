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
        float p;
        float i;
        float d;
    };
    
    struct sensor_t {
        int32_t     left_wheel_count;
        int32_t     right_wheel_count;
        int16_t     sonar_distance;
        bool        touch_pressed;
        int16_t     gyro_angle;
        rgb_raw_t   rgb;
        uint64_t    clock_time;
        int         battery_current;
        int         battery_voltage;
    };

    struct normality_t {
        bool sonar;
        bool touch;
        bool gyro;
        bool color;
        bool left_wheel;
        bool right_wheel;
    };    
}