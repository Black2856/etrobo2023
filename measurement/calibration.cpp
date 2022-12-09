#include "calibration.h"

#include <functional>

Calibration::Calibration(){
}

Calibration::~Calibration(){
}

void Calibration::addBrightness(){
    aryBrightness.push_back(ev3->colorSensor.getBrightness());
}

BrightnessData Calibration::getBrightnessData(const int8_t idx){
    BrightnessData brightnessData;
    aryBrightness.sort();
    auto itr = aryBrightness.begin();
    for(int i = 1; i < idx; i++){
        itr++;
    }
    brightnessData.min = *itr;

    aryBrightness.sort(std::greater<int8_t>());
    itr = aryBrightness.begin();
    for(int i = 1; i < idx; i++){
        itr++;
    }
    brightnessData.max = *itr;
    brightnessData.avg = (brightnessData.max + brightnessData.min) / 2;
    brightnessData.gain = (float)(SIM_MAX_BRIGHTNESS - SIM_MIN_BRIGHTNESS) / (float)(brightnessData.max - brightnessData.min);

    return brightnessData;
}

float Calibration::getCorrectionVal(int8_t brightness, BrightnessData brightnessData){
    float ret = (((float)brightness - (float)brightnessData.min) / ((float)brightnessData.max - (float)brightnessData.min)) * ((float)SIM_MAX_BRIGHTNESS - (float)SIM_MIN_BRIGHTNESS) + (float)SIM_MIN_BRIGHTNESS;
    return ret;
}