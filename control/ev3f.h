#ifndef EV3F_H

#include "stdio.h"
#include "settings.h"
#include "Clock.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "TouchSensor.h"
#include "SonarSensor.h"

using namespace ev3api;

class EV3{ //EV3機能のSingleton管理クラス
public:
  static EV3* getInstance();
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;
  GyroSensor gyroSensor;
  SonarSensor sonarSensor;
  TouchSensor touchSensor;

  Clock clock;

  int16_t GyroSensor_getAngle();

private:
    EV3();
    ~EV3();
    static EV3* m_EV3;
};

#define EV3F_H
#endif