#include "measurement_core.h"
#include "stdio.h"

MeasurementCore* MeasurementCore::m_Measurement = NULL;

MeasurementCore::MeasurementCore(){}

MeasurementCore::~MeasurementCore(){}

MeasurementCore* MeasurementCore::getInstance(){
    if (m_Measurement == NULL){
        m_Measurement = new MeasurementCore();
    }
    return m_Measurement;
}

void MeasurementCore::sensorOutput(){
    //rgb_raw_t rgb_val;
    //ev3->colorSensor.getRawColor(rgb_val);
    //dataIO->addData("brightness", (int)ev3->colorSensor.getBrightness());
    //dataIO->addData("ambient", (int)ev3->colorSensor.getAmbient());
    //dataIO->addData("color", (int)color.getColor());
    //rgb_val = color.getRGB();
    //dataIO->addData("R", (int)rgb_val.r);
    //dataIO->addData("G", (int)rgb_val.g);
    //dataIO->addData("B", (int)rgb_val.b);

    //dataIO->addData("Angle", (int)ev3->GyroSensor_getAngle());
    //dataIO->addData("AngleW", (int)this->vector.getAngle());
    //dataIO->addData("AnglerVelocity", (int)ev3->gyroSensor.getAnglerVelocity());

    //dataIO->addData("leftdeg", (int)ev3->leftWheel.getCount());
    //dataIO->addData("rightdeg", (int)ev3->rightWheel.getCount());
}