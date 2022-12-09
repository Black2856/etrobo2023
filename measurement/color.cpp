#include "color.h"
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

void Color::reset(){
  rgb_val_li.clear();
  ev3->colorSensor.getRawColor(rgb_val);
  for (int i = 0; i < 3; i++){
    rgb_val_li.push_front(rgb_val);
  }
}

ColorList Color::getColor(){
  float GB = 0;
  float RG = 0;
  float RB = 0;

  ev3->colorSensor.getRawColor(rgb_val);
  rgb_val.r = rgb_val.r * 1;
  rgb_val.g = rgb_val.g * 1;
  rgb_val.b = rgb_val.b * 0.8;
  rgb_val_li.push_front(rgb_val);
  rgb_val_li.pop_back();

  auto itr = rgb_val_li.begin();
  
  rgb_raw_t rgb1 = *itr;
  itr++;
  rgb_raw_t rgb2 = *itr;
  itr++;
  rgb_raw_t rgb3 = *itr;

  rgb_val.r = rgb1.g;
  rgb_val.g = rgb2.r;
  rgb_val.b = rgb3.b;

  GB = ((float)rgb_val.g + (float)rgb_val.b) / 2;
  RG = ((float)rgb_val.r + (float)rgb_val.g) / 2;
  RB = ((float)rgb_val.r + (float)rgb_val.b) / 2;

  R = (float)rgb_val.r / GB;
  G = (float)rgb_val.g / RB;
  B = (float)rgb_val.b / RG;
  Y = RG / (float)rgb_val.b;

  return judgment();
}

rgb_raw_t Color::getRGB(){
  return rgb_val;
}

ColorList Color::judgment(){
  float R2 = R / Y;
  float G2 = G / Y;
  float B2 = B / G;
  float Y2 = Y / R;

  ColorList list[] = {ColorList::red, ColorList::green, ColorList::blue, ColorList::yellow};
  ColorList color = ColorList::other;
  int maxBrightness = 0;

  float RGBY[] = {R,G,B,Y};
  int j = 0;
  for (int i = 0; i < 3; i++){
    if (RGBY[j] < RGBY[i + 1]){
      j = i + 1;
    }
  }
  color = list[j];

  int RGB[] = {rgb_val.r, rgb_val.g, rgb_val.b};
  j = 0;
  for (int i = 0; i < 2; i++){
    if (RGB[j] < RGB[i + 1]){
      j = i + 1;
    }
  }
  maxBrightness = RGB[j];

  if(maxBrightness > BRIGHTNESS_THRESHHOLD){
    if(Y >= YELLOW_THRESHOLD && color == ColorList::yellow && Y2 > SECOND_THRESHHOLD){
      color = ColorList::yellow;
    }else if(G >= GREEN_THRESHOLD && color == ColorList::green && G2 > SECOND_THRESHHOLD){
      color = ColorList::green;
    }else if(B >= BLUE_THRESHOLD && color == ColorList::blue && B2 > SECOND_THRESHHOLD){
      color = ColorList::blue;
    }else if (R >= RED_THRESHOLD && color == ColorList::red && R2 > SECOND_THRESHHOLD){
      color = ColorList::red;
    }else{
      color = ColorList::other;
    }
  }else{
    color = ColorList::other;
  }
  
  return color;
}