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