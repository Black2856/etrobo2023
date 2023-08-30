/*
 * クラス名:DeviceInOut
 * 作成日:2023/04/12
 * 作成者:杉本
 */
#include "DeviceInOut.h"
#include "setting.h"
// 以下cameraに使用
#include <cstdio>
#include <algorithm>

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
    bool isExist;
    int16_t value = record.sensorData.getSonarDistance(isExist);
    if(isExist == false){
        int16_t newValue = sonarSensor.getDistance();
        this->record.sensorData.setSonarDistance(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}

/* touch */
bool DeviceInOut::touch_isPressed() {
    bool isExist;
    bool value = record.sensorData.getTouchPressed(isExist);
    if(isExist == false){
        bool newValue = touchSensor.isPressed();
        this->record.sensorData.setTouchPressed(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}

/* gyro */
int16_t DeviceInOut::gyro_getAngle() {
    bool isExist;
    int16_t value = record.sensorData.getGyroAngle(isExist);
    if(isExist == false){
        int16_t newValue = gyroSensor.getAngle();
        this->record.sensorData.setGyroAngle(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}

void DeviceInOut::gyro_reset() {
    gyroSensor.reset();
}

/* color */
int8_t DeviceInOut::color_getBrightness() {
    bool isExist;
    int8_t value = record.sensorData.getBrightness(isExist);
    if(isExist == false){
        int8_t newValue = colorSensor.getBrightness();
        this->record.sensorData.setBrightness(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}
rgb_raw_t DeviceInOut::color_getRawColor() {
    bool isExist;
    rgb_raw_t value = record.sensorData.getRGB(isExist);
    if(isExist == false){
        rgb_raw_t newValue;
        colorSensor.getRawColor(newValue);
        this->record.sensorData.setRGB(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}

/* LWheel */
int32_t DeviceInOut::LWheel_getCount() {
    bool isExist;
    int32_t value = record.sensorData.getLeftWheelCount(isExist);
    if(isExist == false){
        int32_t newValue = leftWheel.getCount();
        this->record.sensorData.setLeftWheelCount(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}
void DeviceInOut::LWheel_setPWM(int pwm) {
    leftWheel.setPWM(pwm * LEFT_WHEEL_POWER);
}
void DeviceInOut::LWheel_stop() {
    leftWheel.stop();
}

/* RWheel */
int32_t DeviceInOut::RWheel_getCount() {
    bool isExist;
    int32_t value = record.sensorData.getRightWheelCount(isExist);
    if(isExist == false){
        int32_t newValue = rightWheel.getCount();
        this->record.sensorData.setRightWheelCount(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}
void DeviceInOut::RWheel_setPWM(int pwm) {
    rightWheel.setPWM(pwm * RIGHT_WHEEL_POWER);
}
void DeviceInOut::RWheel_stop() {
    rightWheel.stop();
}

/* clock */
void DeviceInOut::clock_reset() {
    clock.reset();
}
uint64_t DeviceInOut::clock_now() {
    bool isExist;
    uint64_t value = record.sensorData.getClockTime(isExist);
    if(isExist == false){
        uint64_t newValue = clock.now();
        this->record.sensorData.setClockTime(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}
void DeviceInOut::clock_sleep(uint64_t duration) {
    clock.sleep(duration);
}
void DeviceInOut::clock_wait(uint64_t duration) {
    clock.wait(duration);
}

/* battery */
int DeviceInOut::battery_getCurrent() {
    bool isExist;
    int value = record.sensorData.getBatteryCurrent(isExist);
    if(isExist == false){
        int newValue = ev3_battery_current_mA();
        this->record.sensorData.setBatteryCurrent(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}
int DeviceInOut::battery_getVoltage() {
    bool isExist;
    int value = record.sensorData.getBatteryVoltage(isExist);
    if(isExist == false){
        int newValue = ev3_battery_voltage_mV();
        this->record.sensorData.setBatteryVoltage(newValue);
        return newValue;
    }
    //isExist == true
    return value;
}

/* button */
bool DeviceInOut::button_isPressed(button_t button) {
    return ev3_button_is_pressed(button);
}

/* camera */
void DeviceInOut::camera_addToQueue(const char* fileName) {
    std::array<char, IMG_FILENAME_LEN> arr;
    std::copy_n(fileName, IMG_FILENAME_LEN, arr.begin());
    this->imgNameQueue.push_back(arr);
}

bool DeviceInOut::camera_takePhoto() {
    FILE *fp = fopen(IMG_QUEUE,"a");
    if (fp == NULL) {
		printf("撮影待機リストファイルを開けませんでした。\n");
        return false;
	}
    printf("以下のファイル名で画像を撮影、保存します。\n");
    for (size_t i = 0; i < this->imgNameQueue.size(); i++) {
        uint64_t time = clock_now();
        fprintf(fp,"%s_%lu.png\n", this->imgNameQueue[i].data(), time);
        printf("%s_%lu.png\n", this->imgNameQueue[i].data(), time);
    }
    imgNameQueue.clear();
    fclose(fp);
    return true;
}

int DeviceInOut::camera_getQueueSize() {
    FILE *fp = fopen(IMG_QUEUE, "r");
    if (fp == NULL) {
		printf("撮影待機リストファイルを開けませんでした。\n");
        return 0;
	}

    int lineCount = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    fclose(fp);

    return lineCount;
}