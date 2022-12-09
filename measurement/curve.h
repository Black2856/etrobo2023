#ifndef CURVE_H
#include "vector.h"
#include "ev3f.h"
#include "calibration.h"
#include <cmath>

class Curve{ //走行体の安定度を返す (直進しているほど0に近くなる)
public:
  void updateCurve(BrightnessData brightnessData, float fix); //計算
  float getCurve();
  void resetCurve();

private:
  EV3 *ev3 = EV3::getInstance();
  Vector vector;
  
  float curve = 0;
};

#define CURVE_H
#endif