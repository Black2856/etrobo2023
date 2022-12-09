#ifndef CONTROL_H
#include "stdio.h"
#include "pid.h"
#include "run.h"

class Control{ //制御系のSingleton管理クラス
public:
    static Control* getInstance();

    PID pid;
    Run run;
private:
    Control();
    ~Control();
    static Control* m_Control;
};

#define CONTROL_H
#endif