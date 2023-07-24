/*
 * クラス名:Manual
 * 作成日:2023/07/24
 * 作成者:船田
 */
#ifndef MANUAL_H
#define MANUAL_H

#include "Calc.h"

class Manual {
public:
    void execute();
    void straight();
    void centerRotation();
    void wheelRotation();

private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
}

#endif  // MANUAL_H