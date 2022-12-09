#include "pid.h"
#include "settings.h"
#include "stdio.h"

void PID::reset(){
  this->error[0] = 0;
  this->error[1] = 0;
  this->integral = 0;
}

float PID::execution(const float value, const float target){
  float p,i,d;

  error[1] = error[0];
  error[0] = value - target;
  integral += (error[0] + error[1]) / 2 * ((float)ORDER_T / 1000);

  p = this->pidparam.KP * error[0];
  i = this->pidparam.KI * integral;
  d = this->pidparam.KD * (error[0] - error[1]) / ((float)ORDER_T / 1000);
  return (p + i + d);
}

float PID::exclusive(const float val,const float min, const float max){
  if(val > max){
    return max;
  }else if(val < min){
    return min;
  }
  return val;
}

void PID::setPID(const float KP, const float KI, const float KD){
  reset();
  this->pidparam.KP = KP;
  this->pidparam.KI = KI;
  this->pidparam.KD = KD;
  error[0] = 0;
  error[1] = 0;
} 

void PID::setPID(const PIDparam pidparam){
  this->pidparam = pidparam;
  error[0] = 0;
  error[1] = 0;
}

PIDparam PID::getPID(){
  return this->pidparam;
}