#include "curve.h"

void Curve::updateCurve(BrightnessData brightnessData, float fix){
  vector.addAnglerVelocity();
  float a = std::pow(ev3->colorSensor.getBrightness() - brightnessData.avg, 2);
  float b = a * fix * vector.getRotate(10);
  curve = b + curve * 0.9;
}

float Curve::getCurve(){
  return curve;
}

void Curve::resetCurve(){
  curve = 0;
}