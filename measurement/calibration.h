#ifndef CALIBRATION_H
#include "settings.h"
#include "ev3f.h"
#include <list>

using namespace std;

struct BrightnessData{
    int8_t max = 0;
    int8_t min = 0;
    int8_t avg = 0;
    float gain = 1; //元値からの係数
};

class Calibration{
public:
    Calibration();
    ~Calibration();
    void addBrightness();//反射光の標本データを追加
    BrightnessData getBrightnessData(const int8_t idx);//idx : 上位%の値をminMaxに入れるか
    float getCorrectionVal(int8_t brightness, BrightnessData brightnessData);//シュミレータ環境値に変換
private:
    EV3 *ev3 = EV3::getInstance();
    list<int8_t> aryBrightness; //反射光の記録領域
};

#define CALIBRATION_H
#endif