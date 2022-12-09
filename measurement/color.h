#ifndef COLOR_H
#include "ev3f.h"
#include "settings.h"
#include <list>

using namespace std;

enum class ColorList{
    other  = 0,
    red    = 1,
    green  = 2,
    blue   = 3,
    yellow = 4
};

class Color{
public:
  void reset();//カラーリストの初期化
  ColorList getColor();//カラーセンサのRGB値から色を判断する 閾値はsettings.hを参照
  rgb_raw_t getRGB();
private:
  rgb_raw_t rgb_val;
  list<rgb_raw_t> rgb_val_li;
  int idx = 0;
  EV3 *ev3 = EV3::getInstance();
  float R = 0;
  float G = 0;
  float B = 0;
  float Y = 0;

  ColorList judgment();
};

#define COLOR_H
#endif