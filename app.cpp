#include "app.h"

#include "setting.h"
#include "Clock.h"
#include "manage_scenario.h"
#include "manage_scene.h"
#include "Record.h"
#include "GeneralData.h"
#include "unit.h"
#include "ReadSig.h"
using namespace ev3api;

class Main {
public:
    void run();
private:
    Clock clock;
    ReadSig readSig;

    Record& record = Record::getInstance();
    GeneralData& generalData = GeneralData::getInstance();

    Manage_scenario* manage_scenario;
};

void Main::run() {
    readSig.main();
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
calibration.makeTAKE_PHOTO(1, 1);
calibration.makeCALIBRATION("record:brightness");
calibration.makeMANUAL_PID(2, 2, 70.0, 450.0);
calibration.makeCALIBRATION("stop");
calibration.makeSTOP(3, 0);
calibration.makeMANUAL_PID(4, 5, 80.0, 1.0);
calibration.makeSTOP(5, 0);
manage_scenario.add(calibration);

Manage_scene ready("ready");
ready.makeSTOP(6, 0.0);
manage_scenario.add(ready);

Manage_scene run("run");
run.makeTRACE(7, 85.0, -0.12, 0.0, -0.1, 0.5);
run.makeTRACE(8, 65.0, -1.1, 0.0, -1.0, 0.4);
run.makeTRACE(9, 85.0, -0.12, 0.0, -0.1, 0.5);
run.makeTRACE(10, 60.0, -1.1, 0.0, -1.0, 0.3);
run.makeSTOP(11, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeMANUAL_PID(12, 2.0, 60.0, -15.0);
doubleloop.makeTRACE(13, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(14, 2.0, 60.0, 10.0);
doubleloop.makeTRACE(15, 60.0, -0.57, 0.0, -0.32, 0.5);
doubleloop.makeMANUAL_PID(16, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(17, 0.0);
doubleloop.makeMANUAL_PID(18, 2.0, 60.0, -95.0);
doubleloop.makeTRACE(19, 60.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeTRACE(20, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(21, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(22, 0.0);
doubleloop.makeMANUAL_PID(23, 2.0, 60.0, -95.0);
doubleloop.makeTRACE(24, 60.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeTRACE(25, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeTRACE(26, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(27, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(28, 60.0, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeTRACE(29, 75.0, -0.57, 0.0, -0.32, 0.5);
doubleloop.makeMANUAL_PID(30, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(31, 0.0);
doubleloop.makeMANUAL_PID(32, 2.0, 60.0, 95.0);
doubleloop.makeTRACE(33, 60.0, -0.57, 0.0, -0.32, 0.5);
doubleloop.makeTRACE(34, 75.0, -0.57, 0.0, -0.32, 0.5);
doubleloop.makeSTOP(35, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeMANUAL_PID(36, 2.0, 60.0, -90.0);
block.makeMANUAL_PID(37, 1.0, 50.0, 50.0);
block.makeSTOP(38, 0.0);
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