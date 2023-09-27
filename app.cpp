#include "app.h"

#include "setting.h"
#include "Clock.h"
#include "manage_scenario.h"
#include "manage_scene.h"
#include "Record.h"
#include "GeneralData.h"
#include "unit.h"

using namespace ev3api;

class Main {
public:
    void run();
private:
    Clock clock;

    Record& record = Record::getInstance();
    GeneralData& generalData = GeneralData::getInstance();

    Manage_scenario* manage_scenario;
};

void Main::run() {
    bool result;

    Manage_scenario manage_scenario;

    //#<make_scenario>
Manage_scene main("main");
main.makeCALL_SCENARIO("ready");
main.makeCALL_SCENARIO("calibration");
main.makeCALL_SCENARIO("ready");
main.makeCALL_SCENARIO("run");
main.makeCALL_SCENARIO("doubleloop");
manage_scenario.add(main);

Manage_scene calibration("calibration");
calibration.makeSTOP(0, 0);
calibration.makeCALIBRATION("record:brightness");
calibration.makeMANUAL_PID(1, 2, 70.0, 450.0);
calibration.makeCALIBRATION("stop");
calibration.makeSTOP(2, 0);
calibration.makeCALIBRATION("record:color");
calibration.makeMANUAL_PID(3, 2, 70.0, 360.0);
calibration.makeCALIBRATION("stop");
calibration.makeSTOP(4, 0);
calibration.makeMANUAL_PID(5, 5, 70.0, 1.0);
calibration.makeSTOP(6, 0);
manage_scenario.add(calibration);

Manage_scene ready("ready");
ready.makeSTOP(7, 0.0);
manage_scenario.add(ready);

Manage_scene run("run");
run.makeTRACE(8, 85.0, -0.055, 0.0, -0.07, 0.5);
run.makeTRACE(9, 65.0, -0.9, 0.0, -0.42, 0.4);
run.makeTRACE(10, 85.0, -0.055, 0.0, -0.07, 0.5);
run.makeTRACE(11, 60.0, -0.84, 0.0, -0.42, 0.3);
run.makeSTOP(12, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeMANUAL_PID(13, 2.0, 60.0, -15.0);
doubleloop.makeTRACE(14, 55.0, 0.4, 0.0, 0.15, 0.5);
doubleloop.makeTRACE(15, 55.0, 0.4, 0.0, 0.15, 0.5);
doubleloop.makeMANUAL_PID(16, 2.0, 60.0, 15.0);
doubleloop.makeMANUAL_PID(17, 1.0, 60.0, 50.0);
doubleloop.makeMANUAL_PID(18, 2.0, 60.0, 10.0);
doubleloop.makeTRACE(19, 55.0, -0.4, 0.0, -0.15, 0.5);
doubleloop.makeMANUAL_PID(20, 2.0, 60.0, -15.0);
doubleloop.makeTRACE(21, 55.0, 0.4, 0.0, 0.15, 0.5);
doubleloop.makeMANUAL_PID(22, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(23, 55.0, -0.4, 0.0, -0.15, 0.5);
doubleloop.makeTRACE(24, 60.0, -0.84, 0.0, -0.3, 0.3);
doubleloop.makeTRACE(25, 85.0, -0.055, 0.0, -0.07, 0.5);
doubleloop.makeSTOP(26, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeMANUAL_PID(27, 2.0, 60.0, -90.0);
block.makeMANUAL_PID(28, 1.0, 50.0, 50.0);
block.makeSTOP(29, 0.0);
manage_scenario.add(block);

    //#</make_scenario>

    this->manage_scenario = &manage_scenario;
    this->manage_scenario->update();

    while(1) {
        result = this->manage_scenario->execute();
        this->record.appendSensorData();
        this->clock.sleep(CYCLE);
        if (result == true) {
            break;
        }
    }
}

void main_task(intptr_t unused) {
    Main main;
    main.run();
    ext_tsk();
}