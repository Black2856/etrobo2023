/*
 * クラス名:DeviceInOut
 * 作成日:2023/04/12
 * 作成者:杉本
 */
#include "DeviceInOut.h"
#include "setting.h"
// 以下cameraに使用
#include <cstdio>

DeviceInOut* DeviceInOut::instance = NULL;

DeviceInOut::DeviceInOut():
    sonarSensor (SONAR_SENSOR),
    touchSensor (TOUCH_SENSOR),
    gyroSensor  (GYRO_SENSOR),
    colorSensor (COLOR_SENSOR), 
    leftWheel   (LEFT_WHEEL), 
    rightWheel  (RIGHT_WHEEL){}

DeviceInOut& DeviceInOut::getInstance() {
    if (!instance) {
        instance = new DeviceInOut();
    }
    return *instance;
}

/*** 以下各インスタンス関数定義 ***/
/* sonar */
int16_t DeviceInOut::sonar_getDistance() {
    return sonarSensor.getDistance();
}

/* touch */
bool DeviceInOut::touch_isPressed() {
    return touchSensor.isPressed();
}

/* gyro */
int16_t DeviceInOut::gyro_getAngle() {
    return gyroSensor.getAngle();
}

void DeviceInOut::gyro_reset() {
    gyroSensor.reset();
}

/* color */
int8_t DeviceInOut::color_getBrightness() {
    return colorSensor.getBrightness();
}
rgb_raw_t DeviceInOut::color_getRawColor() {
    rgb_raw_t rgb;
    colorSensor.getRawColor(rgb);
    return rgb;
}

/* LWheel */
int32_t DeviceInOut::LWheel_getCount() {
    return leftWheel.getCount();
}
void DeviceInOut::LWheel_setPWM(int pwm) {
    leftWheel.setPWM(pwm);
}
void DeviceInOut::LWheel_stop() {
    leftWheel.stop();
}

/* RWheel */
int32_t DeviceInOut::RWheel_getCount() {
    return rightWheel.getCount();
}
void DeviceInOut::RWheel_setPWM(int pwm) {
    rightWheel.setPWM(pwm);
}
void DeviceInOut::RWheel_stop() {
    rightWheel.stop();
}

/* clock */
void DeviceInOut::clock_reset() {
    clock.reset();
}
uint64_t DeviceInOut::clock_now() {
    return clock.now();
}
void DeviceInOut::clock_sleep(uint64_t duration) {
    clock.sleep(duration);
}
void DeviceInOut::clock_wait(uint64_t duration) {
    clock.wait(duration);
}

/* battery */
int DeviceInOut::battery_getCurrent() {
    return ev3_battery_current_mA();
}
int DeviceInOut::battery_getVoltage() {
    return ev3_battery_voltage_mV();
}

/* button */
bool DeviceInOut::button_isPressed(button_t button) {
    return ev3_button_is_pressed(button);
}

/* camera */
void DeviceInOut::camera_addToQueue(const char* fileName) {
    this->imgNameQueue.push_back(fileName);
}

bool DeviceInOut::camera_takePhoto() {
    FILE *fp = fopen(IMG_QUEUE_PATH,"a");
    if (fp == NULL) {
		printf("撮影待機リストファイルを開けませんでした。\n");
        return false;
	}
    printf("以下のファイル名で画像を撮影、保存します。\n");
    for(auto name : imgNameQueue) {
        fprintf(fp,"%s.jpg\n", name);
        printf("%s.jpg\n", name);
    }
    imgNameQueue.clear();
    fclose(fp);
    return true;
}

int DeviceInOut::camera_getQueueSize() {
    FILE* fp = std::fopen(IMG_QUEUE_PATH, "r");
    if (fp == NULL) {
		printf("撮影待機リストファイルを開けませんでした。\n");
        return 0;
	}

    int lineCount = 0;
    int ch;
    while ((ch = std::fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    std::fclose(fp);

    return lineCount;
}