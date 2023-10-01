#include "app.h"

#include "setting.h"
#include "Clock.h"
#include "custom_scenario.h"
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
    Custom_scenario custom_scenario;

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
calibration.makeMANUAL_PID(3, 5, 80.0, 1.0);
calibration.makeSTOP(4, 0);
manage_scenario.add(calibration);

Manage_scene ready("ready");
ready.makeSTOP(5, 0.0);
manage_scenario.add(ready);

Manage_scene run("run");
run.makeTRACE(6, 85.0, -0.12, 0.0, -0.1, 0.5);
run.makeTRACE(7, 65.0, -1.1, 0.0, -1.0, 0.4);
run.makeTRACE(8, 85.0, -0.12, 0.0, -0.1, 0.5);
run.makeTRACE(9, 60.0, -1.1, 0.0, -1.0, 0.3);
run.makeSTOP(10, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeMANUAL_PID(11, 2.0, 60.0, -15.0);
doubleloop.makeTRACE(12, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(13, 2.0, 60.0, 10.0);
doubleloop.makeTRACE(14, 60.0, -0.57, 0.0, -0.32, 0.5);
doubleloop.makeSTOP(15, 0.0);
doubleloop.makeMANUAL_PID(16, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(17, 0.0);
doubleloop.makeTAKE_PHOTO(18, 1.0);
doubleloop.makeSTOP(19, 0.0);
doubleloop.makeMANUAL_PID(2.0, 60.0, -93.0);
doubleloop.makeTRACE(20, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeSTOP(21, 0.0);
doubleloop.makeMANUAL_PID(22, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(23, 0.0);
doubleloop.makeTAKE_PHOTO(24, 1.0);
doubleloop.makeSTOP(25, 0.0);
doubleloop.makeMANUAL_PID(2.0, 60.0, -93.0);
doubleloop.makeTRACE(26, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeTRACE(27, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(28, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(29, 60.0, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeMANUAL_PID(30, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(31, 0.0);
doubleloop.makeTAKE_PHOTO(32, 1.0);
doubleloop.makeSTOP(33, 0.0);
doubleloop.makeMANUAL_PID(34, 2.0, 70.0, 135.0);
doubleloop.makeMANUAL_PID(35, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(36, 60.0, -0.57, 0.0, -0.32, 1.0);
doubleloop.makeSTOP(37, 0.0);
doubleloop.makeMANUAL_PID(38, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(39, 0.0);
doubleloop.makeTAKE_PHOTO(40, 1.0);
doubleloop.makeSTOP(41, 0.0);
doubleloop.makeMANUAL_PID(42, 2.0, 70.0, 135.0);
doubleloop.makeMANUAL_PID(43, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(44, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeSTOP(45, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(46, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(47, 2.0, 60.0, -90.0);
straight.makeMANUAL_PID(48, 1.0, 50.0, 50.0);
straight.makeSTOP(49, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(50, 2.0, 60.0, -90.0);
right.makeMANUAL_PID(51, 1.0, 50.0, 50.0);
right.makeSTOP(52, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(53, 2.0, 60.0, -90.0);
left.makeMANUAL_PID(54, 1.0, 50.0, 50.0);
left.makeSTOP(55, 0.0);
manage_scenario.add(left);

    //#</make_scenario>

    this->manage_scenario = &manage_scenario;
    this->manage_scenario->update();

    while(1) {
        result = this->manage_scenario->execute();
        this->custom_scenario.mainProcess(this->manage_scenario);

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