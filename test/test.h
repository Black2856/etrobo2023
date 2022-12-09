#ifdef test

#include "Motor.h"
using namespace ev3api;

Motor leftWheel;
Motor rightWheel;
ColorSensor colorSensor;
GyroSensor gyroSensor;
SonarSensor sonarSensor;
TouchSensor touchSensor;

Clock clock;

#define test