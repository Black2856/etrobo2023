#ifndef BASIC_H
#include <list>
#include "ev3f.h"
#include "math.h"
#include "settings.h"

using namespace std;

class Vector{
public:
  Vector();

  void addAnglerVelocity(); //角速度をリストに追加する
  void resetAnglerVelocity(); //角速度リストを初期化
  float getStable(const int idx); //現時点からidxまでの安定度(各速度の標準偏差)を返す
  float getRotate(const int idx); //現時点からidxまでの方向(角速度の総和)を返す

  void setRotateOffset(const int32_t left, const int32_t right); //車輪回転数のオフセット
  void setRotateOffset();
  float getScalar(); //(車輪回転数から)走行体の移動距離を返す
  float getAngle(); //(車輪回転数から)走行体の角度を返す
private:
  EV3 *ev3 = EV3::getInstance();
  list<int16_t> aryAnglerVelocity;
  int8_t maxAry = 100;

  int32_t offset[2] = {0, 0};
  int16_t anglerVelocity = 0; 
};

#define BASIC_H
#endif