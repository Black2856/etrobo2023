#include "run.h"
#include "cstdlib"

void Run::update(){
    //PWM計算
    int PWMdiff = (runParam.PWM - lastRunParam.PWM);
    float transition = 0;
    uint64_t time = clock.now();
    if(runParam.transitionTime <= time){
        transition = 1;
    }else{
        transition = (float)(time/1000) / (float)(runParam.transitionTime/1000);
    }
    int setPWM = runParam.PWM - (int)((float)PWMdiff * (1 - transition));
    //ステアリング計算
    float rightSteering = 0;
    float leftSteering = 0;
    if(runParam.steeringType == 0){
        steeringA(rightSteering, leftSteering, setPWM);
    }else if(runParam.steeringType == 1){
        steeringB(rightSteering, leftSteering);
    }

    ev3->leftWheel.setPWM(setPWM - (int)leftSteering);
    ev3->rightWheel.setPWM(setPWM - (int)rightSteering);
    //printf("%d , %d \n",setPWM - (int)leftSteering , setPWM * 2 * (float)std::abs(runParam.steering) / 100);
}

void Run::steeringA(float &rightSteering, float &leftSteering, const int setPWM){
    if(runParam.steering > 0){
        rightSteering = setPWM * 2 * (float)std::abs(runParam.steering) / 100;
    }else if(runParam.steering < 0){
        leftSteering = setPWM * 2 * (float)std::abs(runParam.steering) / 100;
    }
}

void Run::steeringB(float &rightSteering, float &leftSteering){
    if(runParam.steering > 0){
        rightSteering = (float)std::abs(runParam.steering);
        leftSteering = -(float)std::abs(runParam.steering);
    }else if(runParam.steering < 0){
        rightSteering = -(float)std::abs(runParam.steering);
        leftSteering = (float)std::abs(runParam.steering);
    }
}

void Run::setParam(RunParam runParam){
    if(!(this->runParam.PWM == runParam.PWM && this->runParam.transitionTime == runParam.transitionTime)){
        clock.reset();
        this->lastRunParam = this->runParam;
        this->runParam.PWM = runParam.PWM;
    }else{
        this->lastRunParam.steering = this->runParam.steering;
        this->lastRunParam.steeringType = this->runParam.steeringType;
        this->lastRunParam.transitionTime = this->runParam.transitionTime;
    }
    this->runParam.steering = runParam.steering;
    this->runParam.transitionTime = runParam.transitionTime;
    this->runParam.steeringType = runParam.steeringType;
}

void Run::setParam(int PWM, int steering, uint64_t transitionTime, uint8_t steeringType){
    if(!(this->runParam.PWM == PWM && this->runParam.transitionTime == transitionTime)){
        clock.reset();
        this->lastRunParam = this->runParam;
        this->runParam.PWM = PWM;
    }else{
        this->lastRunParam.steering = this->runParam.steering;
        this->lastRunParam.steeringType = this->runParam.steeringType;
        this->lastRunParam.transitionTime = this->runParam.transitionTime;
    }
    this->runParam.steering = steering;
    this->runParam.transitionTime = transitionTime;
    this->runParam.steeringType = steeringType;
}