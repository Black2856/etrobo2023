/*
 * クラス名:LineTrace
 * 作成日:2023/06/26
 * 作成者:松尾
 */
#include "LineTrace.h"

LineTrace::LineTrace():
    device(DeviceInOut::getInstance()),
    mPID([0,0,0]){}

void LineTrace::Trace(int pwm){
    
    // TARGETをとりあえず18とする
    float gain=pidControl.calc(device.color_getBrightness(), 18);
    device.LWheel(pwm-gain);
    device.RWheel(pwm+gain);
    
}

    