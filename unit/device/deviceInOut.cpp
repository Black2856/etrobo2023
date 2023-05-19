/*
 * クラス名:deviceInOut
 * 作成日：2023/04/12
 * 作成者:杉本
 * 修正日:2023/05/19
 * 修正者:杉本
 * ver:2.0.0
 */
#include "deviceInOut.h"
#include "setting.h"

deviceInOut* deviceInOut::instance = NULL;

deviceInOut::deviceInOut():
    sonarSensor (SONAR_SENSOR),
    touchSensor (TOUCH_SENSOR),
    gyroSensor  (GYRO_SENSOR),
    colorSensor (COLOR_SENSOR), 
    leftWheel   (LEFT_WHEEL), 
    rightWheel  (RIGHT_WHEEL){}

deviceInOut& deviceInOut::getInstance() {
    if (!instance) {
        instance = new deviceInOut();
    }
    return *instance;
}

/*** 以下各インスタンス関数定義 ***/
/* sonar */
int16_t deviceInOut::sonar_getDistance() {
    return sonarSensor.getDistance();
}

/* touch */
bool deviceInOut::touch_isPressed() {
    return touchSensor.isPressed();
}

/* gyro */
int16_t deviceInOut::gyro_getAngle() {
    return gyroSensor.getAngle();
}

void deviceInOut::gyro_reset() {
    gyroSensor.reset();
}

/* color */
int8_t deviceInOut::color_getBrightness() {
    return colorSensor.getBrightness();
}
rgb_raw_t deviceInOut::color_getRawColor() {
    rgb_raw_t rgb;
    colorSensor.getRawColor(rgb);
    return rgb;
}

/* LWheel */
int32_t deviceInOut::LWheel_getCount() {
    return leftWheel.getCount();
}
void deviceInOut::LWheel_setPWM(int pwm) {
    leftWheel.setPWM(pwm);
}
void deviceInOut::LWheel_stop() {
    leftWheel.stop();
}

/* RWheel */
int32_t deviceInOut::RWheel_getCount() {
    return rightWheel.getCount();
}
void deviceInOut::RWheel_setPWM(int pwm) {
    rightWheel.setPWM(pwm);
}
void deviceInOut::RWheel_stop() {
    rightWheel.stop();
}

/* clock */
void deviceInOut::clock_reset() {
    clock.reset();
}
uint64_t deviceInOut::clock_now() {
    return clock.now();
}
void deviceInOut::clock_sleep(uint64_t duration) {
    clock.sleep(duration);
}
void deviceInOut::clock_wait(uint64_t duration) {
    clock.wait(duration);
}

/* battery */
int deviceInOut::battery_getCurrent() {
    return ev3_battery_current_mA();
}
int deviceInOut::battery_getVoltage() {
    return ev3_battery_voltage_mV();
}

/* button */
bool deviceInOut::button_isPressed(button_t button) {
    return ev3_button_is_pressed(button);
}
