namespace unit {
    enum color_t {
        RED,
        BLUE,
        YELLOW,
        GREEN,
        WHITE,
        BLACK,
    };

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
        int         left_wheel_count;
        int         right_wheel_count;
        int         sonar_distance;
        bool        touch_pressed;
        int         gyro_angle;
        rgb_raw_t   rgb;
        int         clock_time;
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