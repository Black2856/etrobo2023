#include "settings.h"
#include "run_area.h"
#include "sectionList.h"
#include "control.h"
#include "ev3f.h"
#include "measurement_core.h"
#include "calibration.h"

#include "stdio.h"
#include "cstdlib"

using namespace std;

EV3 *ev3 = EV3::getInstance();
Control *control = Control::getInstance();
MeasurementCore *measurementCore = MeasurementCore::getInstance();
BrightnessData brightnessData;

SectionList returnSection = SectionList::Section99;

////////////////////////////////////////////////////////////////終了
void Section99::entry(){
    control->run.setParam(0,0,0,0);
    control->run.update();
    ev3->leftWheel.stop();
    ev3->rightWheel.stop();
    dataIO->addData("end", "end");
}

void Section99::main(){
}

void Section99::condition(){
}

////////////////////////////////////////////////////////////////初期化待ち
void Section00::entry(){
    tslp_tsk(3000 * 1000); //初期化待ち
    control->run.setParam(5,-100,0,0);
}

void Section00::main(){
    control->run.update();
}

void Section00::condition(){
    if((int)ev3->rightWheel.getCount() > 1){
        control->run.setParam(0,0,0,0);
        control->run.update();
/*
        brightnessData.max = 35;
        brightnessData.min = 4;
        brightnessData.avg = 19;
        brightnessData.gain = 1.064516;
*/
        transition(SectionList::Section01);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション(情報取得中)
void Section01::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0, 0);
}

void Section01::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 450 * ROTATE_CORRECTION + 5);

    if(fix >= 10){
        fix = 10;
    }else if(fix <= -10){
        fix = -10;
    }
    control->run.setParam((int)fix, 100, 0, 0);
    control->run.update();
    measurementCore->calibration.addBrightness();
}

void Section01::condition(){
    if(measurementCore->vector.getAngle() >= 450 * ROTATE_CORRECTION){
        brightnessData = measurementCore->calibration.getBrightnessData(10);
        //printf("%d,%d,%d\n",brightnessData.max,brightnessData.min,brightnessData.avg);
        dataIO->addData("max", (int)brightnessData.max);
        dataIO->addData("min", (int)brightnessData.min);
        dataIO->addData("avg", (int)brightnessData.avg);
        dataIO->addData("gain", (float)brightnessData.gain);

        control->run.setParam(0,0,0,0);
        control->run.update();
        transition(SectionList::Section02);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション(テスト)
void Section02::entry(){
    control->pid.setPID(1, 0.1, 0.2);
}

void Section02::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    if(fix >= 10){
        fix = 10;
    }else if(fix <= -10){
        fix = -10;
    }
    control->run.setParam(fix,100,0,0);
    control->run.update();
}

void Section02::condition(){
    if((int)ev3->colorSensor.getBrightness() == brightnessData.avg){
        control->run.setParam(0,0,0,0);
        control->run.update();
        returnSection = SectionList::Section03;
        transition(SectionList::Section03);
    }
}
////////////////////////////////////////////////////////////////スタート待機
void Section03::entry(){
    control->run.setParam(0, 0, 0, 0);
    control->run.update();
}

void Section03::main(){
}

void Section03::condition(){
    if(ev3->touchSensor.isPressed()){
        measurementCore->color.reset();
        measurementCore->curve.resetCurve();
        measurementCore->vector.setRotateOffset();
        measurementCore->vector.resetAnglerVelocity();
        ev3->gyroSensor.reset();
        transition(SectionList::Section04);
    }
}
////////////////////////////////////////////////////////////////走行エリア(PWM 100 直進)
void Section04::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
    control->pid.setPID(1.5,0,0.15); //シミュレータ2.4 0 0.4
}

void Section04::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    //control->run.setParam(100 - measurementCore->vector.getStable(100) * 1.8, (int)fix, 0, 0);
    control->run.setParam(100, (int)fix, 0, 0);
    control->run.update();

    measurementCore->vector.addAnglerVelocity();
    dataIO->addData("fix", (int)fix);
    dataIO->addData("stable10", measurementCore->vector.getStable(10));
    measurementCore->curve.updateCurve(brightnessData, fix);
    dataIO->addData("curve", measurementCore->curve.getCurve());
    //dataIO->addData("rotate", measurementCore->vector.getRotate(10));
    dataIO->addData("Angle", measurementCore->vector.getAngle());
    dataIO->addData("Scalar", measurementCore->vector.getScalar());
}

void Section04::condition(){
    if(measurementCore->vector.getScalar() > 80){
        transition(SectionList::Section05);
    }
}
////////////////////////////////////////////////////////////////走行エリア(PWM 30 カーブ)

void Section05::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.3,0,0.1);
}

void Section05::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(30, (int)fix, 500 * 1000, 1);
    control->run.update();
    dataIO->addData("Scalar", measurementCore->vector.getScalar());
    dataIO->addData("deg", ev3->GyroSensor_getAngle());
    measurementCore->vector.addAnglerVelocity();
    measurementCore->curve.updateCurve(brightnessData, fix);
}

void Section05::condition(){
    if(abs(measurementCore->curve.getCurve() < 5000) && measurementCore->vector.getScalar() > 65 && measurementCore->vector.getAngle() < -88){
        transition(SectionList::Section06);
    }else if(abs(measurementCore->curve.getCurve() < 2000) && measurementCore->vector.getScalar() > 65 && measurementCore->vector.getAngle() < -80){
        transition(SectionList::Section06);
    }
/*
    if(abs(measurementCore->curve.getCurve() < 2500) && measurementCore->vector.getScalar() > 65){
        transition(SectionList::Section06);
    }
*/
}

////////////////////////////////////////////////////////////////走行エリア(PWM 100 直進)
void Section06::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
    control->pid.setPID(1.5,0,0.15);
}

void Section06::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(100, (int)fix, 0, 0);
    control->run.update();

    measurementCore->vector.addAnglerVelocity();
}

void Section06::condition(){
    if(measurementCore->vector.getScalar() > 120){
        transition(SectionList::Section07);
    }
}

////////////////////////////////////////////////////////////////走行エリア(PWM 30 カーブ)

void Section07::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0,0,0.1);
}

void Section07::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(30, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section07::condition(){
    if(abs(measurementCore->curve.getCurve() < 5000) && measurementCore->vector.getScalar() > 65 && measurementCore->vector.getAngle() > 88){
        transition(SectionList::Section08);
    }else if(abs(measurementCore->curve.getCurve() < 2000) && measurementCore->vector.getScalar() > 65 && measurementCore->vector.getAngle() > 80){
        transition(SectionList::Section08);
    }
}

////////////////////////////////////////////////////////////////走行エリア(PWM 100 直進)

void Section08::entry(){
    measurementCore->curve.resetCurve();
    control->pid.setPID(1.5,0,0.15);
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
}

void Section08::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(100, (int)fix, 0, 0);
    control->run.update();

    measurementCore->vector.addAnglerVelocity();
}

void Section08::condition(){
    if(measurementCore->vector.getScalar() > 60){
        transition(SectionList::Section30);
    }
}

////////////////////////////////////////////////////////////////調整走行(1) : returnSectionに戻る

void Section20::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
    control->pid.setPID(0,0,0);
}

void Section20::main(){
    control->run.setParam(-7, 0, 0, 0);
    control->run.update();
}

void Section20::condition(){
    if(measurementCore->vector.getScalar() < -10){
        transition(SectionList::Section21);
    }
}

////////////////////////////////////////////////////////////////調整走行(2)

void Section21::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(0.4,0.05,0.06);
}

void Section21::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(7, (int)fix, 0, 1);
    control->run.update();
    measurementCore->curve.updateCurve(brightnessData, fix);
}

void Section21::condition(){
    if(measurementCore->vector.getScalar() > 10){
        if(abs(measurementCore->curve.getCurve()) < 50){
            transition(returnSection);
        }else{
            transition(SectionList::Section20);
        }
    }
}

/*
void Section99::entry(){
    //printf("entry99 ");
}
void Section99::main(){
    //printf("main99 ");
}
void Section99::condition(){
    //printf("condition99 ");
    //printf("%u\n",clock.now());
    if(clock.now() > 10000000){
        transition((int)SectionList::Section01);
    }
}
*/

//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆　ゲームエリア侵入　◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
////////////////////////////////////////////////////////////////走行(PWM 30 カーブ)
void Section30::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0,0,0.1);
}

void Section30::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(30, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section30::condition(){
    if(measurementCore->vector.getScalar() > 200){
        transition(SectionList::Section31);
    }
}
////////////////////////////////////////////////////////////////端点サークルまで走行(PWM 30)

void Section31::entry(){
    measurementCore->color.reset();
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0,0,0.1);
}

void Section31::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(12, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section31::condition(){
    ColorList color = measurementCore->color.getColor();
    bool hit = false;
    if(color == ColorList::red){
        hit = true;
    }else if(color == ColorList::green){
        hit = true;
    }else if(color == ColorList::blue){
        hit = true;
    }else if(color == ColorList::yellow){
        hit = true;
    }
    if(hit == true && clock.now() > ORDER_T * 4 * 1000){
        transition(SectionList::Section32);
    }
}
////////////////////////////////////////////////////////////////回転

void Section32::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.2, 0.1, 0);
    control->run.setParam(0, 0, 0, 0);
}

void Section32::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 45 * ROTATE_CORRECTION + 5);

    if(fix >= 8){
        fix = 8;
    }else if(fix <= -8){
        fix = -8;
    }
    control->run.setParam((int)fix, 100, 0, 0);
    control->run.update();
}

void Section32::condition(){
    if(measurementCore->vector.getAngle() >= 45 * ROTATE_CORRECTION){
        returnSection = SectionList::Section33;
        transition(SectionList::Section80);
    }
}
////////////////////////////////////////////////////////////////サークル手前まで走行
void Section33::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(2.5, 0, 0.5);
}

void Section33::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(10, (int)fix, 500 * 1000, 0);
    control->run.update();
}

void Section33::condition(){
    if(measurementCore->vector.getScalar() > 20){
        transition(SectionList::Section34);
    }
}

////////////////////////////////////////////////////////////////色検知するまで直進
void Section34::entry(){
    measurementCore->color.reset();
    measurementCore->vector.setRotateOffset();
    measurementCore->curve.resetCurve();
    control->run.setParam(10, 0, 0, 0);
}

void Section34::main(){
    control->run.update();
}

void Section34::condition(){
    ColorList color = measurementCore->color.getColor();
    bool hit = false;
    if(color == ColorList::red){
        hit = true;
    }else if(color == ColorList::green){
        hit = true;
    }else if(color == ColorList::blue){
        hit = true;
    }else if(color == ColorList::yellow){
        hit = true;
    }
    if((hit == true && clock.now() > ORDER_T * 4 * 1000) || measurementCore->vector.getScalar() > 13){
        transition(SectionList::Section35);
    }
}
////////////////////////////////////////////////////////////////調整
void Section35::entry(){
    measurementCore->color.reset();
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0.05, 0.1);
}

void Section35::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 0);
    control->run.setParam(10, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section35::condition(){
    if(measurementCore->vector.getScalar() > 8){
        returnSection = SectionList::Section36;
        transition(SectionList::Section80);
    }
}
////////////////////////////////////////////////////////////////回転
void Section36::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0.1, 0);
}

void Section36::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 55 * ROTATE_CORRECTION + 5);

    if(fix >= 8){
        fix = 8;
    }else if(fix <= -8){
        fix = -8;
    }
    control->run.setParam((int)fix, 100, 0, 0);
    control->run.update();
}

void Section36::condition(){
    if(measurementCore->vector.getAngle() >= 55 * ROTATE_CORRECTION){
        returnSection = SectionList::Section37;
        transition(SectionList::Section80);
    }
}
////////////////////////////////////////////////////////////////ラインを検知するまで直進
void Section37::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0.05, 0.1);
}

void Section37::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 0);
    control->run.setParam(10, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section37::condition(){
    if((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData) <= ((SIM_MIN_BRIGHTNESS + SIM_AVG_BRIGHTNESS)/2) && clock.now() > 100 * 1000){
        transition(SectionList::Section03);
    }
}
////////////////////////////////////////////////////////////////調整(未使用)
void Section38::entry(){
    measurementCore->color.reset();
    measurementCore->vector.setRotateOffset();
    control->run.setParam(10, 0, 0, 0);
}

void Section38::main(){
    control->run.update();
}

void Section38::condition(){
    if(measurementCore->vector.getScalar() > 6){
        transition(SectionList::Section39);
    }
}
////////////////////////////////////////////////////////////////一時しのぎ(未使用)
void Section39::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0.1, 0);
}

void Section39::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 30 * ROTATE_CORRECTION + 5);

    if(fix >= 8){
        fix = 8;
    }else if(fix <= -8){
        fix = -8;
    }
    control->run.setParam((int)fix, 100, 0, 0);
    control->run.update();
}

void Section39::condition(){
    if(measurementCore->vector.getAngle() >= 30 * ROTATE_CORRECTION){
        transition(SectionList::Section03);
    }
}

//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆　ゲームエリア動作　◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
//◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
////////////////////////////////////////////////////////////////直進
void Section40::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(3.0,0,0.5);
}

void Section40::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(12, (int)fix, 500 * 1000, 0);
    control->run.update();
}

void Section40::condition(){
    if(measurementCore->vector.getScalar() > 13){
        transition(SectionList::Section43);
    }
}

////////////////////////////////////////////////////////////////回転-90°
void Section41::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0.1, 0);
}

void Section41::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 90 * ROTATE_CORRECTION + 5);

    if(fix >= 8){
        fix = 8;
    }else if(fix <= -8){
        fix = -8;
    }
    control->run.setParam((int)fix, 100, 0, 0);
    control->run.update();
}

void Section41::condition(){
    if(measurementCore->vector.getAngle() >= 90 * ROTATE_CORRECTION){
        transition(returnSection);
    }
}

////////////////////////////////////////////////////////////////回転90°

void Section42::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0, 0);
}

void Section42::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), -90 * ROTATE_CORRECTION - 5);

    if(fix >= 8){
        fix = 8;
    }else if(fix <= -8){
        fix = -8;
    }
    control->run.setParam((int)fix, 100, 0, 0);
    control->run.update();
}

void Section42::condition(){
    if(measurementCore->vector.getAngle() <= -90 * ROTATE_CORRECTION){
        transition(returnSection);
    }
}

////////////////////////////////////////////////////////////////直線補正(1)
void Section43::entry(){
    measurementCore->color.reset();
    measurementCore->vector.setRotateOffset();
    control->run.setParam(10, 0, 0, 0);
}

void Section43::main(){
    control->run.update();
}

void Section43::condition(){
    ColorList color = measurementCore->color.getColor();
    bool hit = false;
    if(color == ColorList::red){
        hit = true;
    }else if(color == ColorList::green){
        hit = true;
    }else if(color == ColorList::blue){
        hit = true;
    }else if(color == ColorList::yellow){
        hit = true;
    }
    if(hit == true){
        transition(SectionList::Section44);
    }
}
////////////////////////////////////////////////////////////////直線補正(2)
void Section44::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0, 0, 0);
}

void Section44::main(){
    float fix = control->pid.execution(measurementCore->vector.getAngle(), 0);
    control->run.setParam(10, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section44::condition(){
    if(measurementCore->vector.getScalar() > 6){
        transition(SectionList::Section80);
    }
}

////////////////////////////////////////////////////////////////区間静止
void Section80::entry(){
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(0,0,0);
    control->run.setParam(0, 0, 0, 0);
}

void Section80::main(){
    control->run.update();
}

void Section80::condition(){
    if(clock.now() > 500 * 1000){
        transition(returnSection);
    }
}

////////////////////////////////////////////////////////////////テスト用
void Section98::entry(){
    measurementCore->color.reset();
    measurementCore->vector.setRotateOffset();
    control->run.setParam(10, 0, 0, 0);
}

void Section98::main(){
    control->run.update();
}

void Section98::condition(){
    ColorList color = measurementCore->color.getColor();
    bool hit = false;
    if(color == ColorList::red){
        hit = true;
    }else if(color == ColorList::green){
        hit = true;
    }else if(color == ColorList::blue){
        hit = true;
    }else if(color == ColorList::yellow){
        hit = true;
    }
    if(hit == true){
        transition(SectionList::Section03);
    }
    /*
    if(clock.now() > 5000 * 1000){
        transition(SectionList::Section03);
    }
    */
}