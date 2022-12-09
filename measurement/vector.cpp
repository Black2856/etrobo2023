#include "vector.h"
#define PI 3.14159

using namespace std;

Vector::Vector(){
  resetAnglerVelocity();
}

void Vector::addAnglerVelocity(){
  if((int8_t)aryAnglerVelocity.size() >= maxAry){
    aryAnglerVelocity.pop_back();
  }
  int16_t nowAnglerVelocity = ev3->GyroSensor_getAngle();
  aryAnglerVelocity.push_front((float)(nowAnglerVelocity - this->anglerVelocity));
  this->anglerVelocity = nowAnglerVelocity;
}

void Vector::resetAnglerVelocity(){
  aryAnglerVelocity.clear();
  this->anglerVelocity = ev3->GyroSensor_getAngle();
}

float Vector::getStable(const int idx){
  float stable = 0;
  int max = idx;
  auto itr = aryAnglerVelocity.begin();
  if((int)aryAnglerVelocity.size() < idx){
    max = (int)aryAnglerVelocity.size();
  }
  for(int i = 0; i < max; i++){
    stable += pow(*itr, 2);
    itr++;
  }
  if(stable == 0){
    return 0;
  }
  stable = sqrt(stable);
  return (stable / idx) * (float)(1000 / ORDER_T);
}

float Vector::getRotate(const int idx){
  float rotate = 0;
  int max = idx;
  auto itr = aryAnglerVelocity.begin();
  if((int)aryAnglerVelocity.size() < idx){
    max = (int)aryAnglerVelocity.size();
  }
  for(int i = 0; i < max; i++){
    if(i < (int)aryAnglerVelocity.size()){
      rotate += *itr;
      itr++;
    }
  }
  if(rotate == 0){
    return 0;
  }
  return rotate;
}

void Vector::setRotateOffset(const int32_t left, const int32_t right){
  this->offset[0] = left;
  this->offset[1] = right;
}

void Vector::setRotateOffset(){
  this->offset[0] = ev3->leftWheel.getCount();
  this->offset[1] = ev3->rightWheel.getCount();
}

float Vector::getScalar(){
  int32_t left = ev3->leftWheel.getCount() - this->offset[0];
  int32_t right = ev3->rightWheel.getCount() - this->offset[1];
  float scalar = 0;
  if(left < right){
    scalar = (float)(right - left) / 2 + left;
    scalar = scalar / 360 * 2 * PI * WHEEL;
  }else if(left > right){
    scalar = (float)(left - right) / 2 + right;
    scalar = scalar / 360 * 2 * PI * WHEEL;
  }else{
    scalar = (float)left / 360 * 2 * PI * WHEEL;
  }

  return scalar;
}

float Vector::getAngle(){
  int32_t left = ev3->leftWheel.getCount() - this->offset[0];
  int32_t right = ev3->rightWheel.getCount() - this->offset[1];
  float angle = 0;

  angle = (float)(right - left);
  angle = angle / 3;

  return angle;
}