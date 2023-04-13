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