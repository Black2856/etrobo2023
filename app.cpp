#include "app.h"

#include "setting.h"
#include "Clock.h"
#include "manage_scenario.h"
#include "manage_scene.h"
#include "Record.h"
#include "GeneralData.h"
#include "unit.h"
#include "ReadSignal.h"
using namespace ev3api;

class Main {
public:
    void run();
private:
    Clock clock;
    ReadSignal readSignal;

    Record& record = Record::getInstance();
    GeneralData& generalData = GeneralData::getInstance();

    Manage_scenario* manage_scenario;
};

void Main::run() {
    readSignal.main();
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
doubleloop.makeTRACE(14, 75.0, 0.5, 0.0, 0.3, 0.5);
doubleloop.makeMANUAL_PID(15, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(16, 50.0, -0.7, 0.0, -0.4, 0.5);
doubleloop.makeMANUAL_PID(17, 2.0, 60.0, 20.0);
doubleloop.makeTRACE(18, 60.0, -0.7, 0.0, -0.4, 0.5);
doubleloop.makeMANUAL_PID(19, 1.0, 60.0, 150.0);
doubleloop.makeMANUAL_PID(20, 2.0, 55.0, -5.0);
doubleloop.makeTRACE(21, 55.0, -1.0, 0.0, -1.0, 0.5);
doubleloop.makeTRACE(22, 60.0, -1.5, 0.0, -1.0, 0.3);
doubleloop.makeTRACE(23, 85.0, -0.12, 0.0, -0.1, 0.5);
doubleloop.makeSTOP(24, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeMANUAL_PID(25, 2.0, 60.0, -90.0);
block.makeMANUAL_PID(26, 1.0, 50.0, 50.0);
block.makeSTOP(27, 0.0);
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