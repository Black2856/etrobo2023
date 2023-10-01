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
doubleloop.makeMANUAL_PID(15, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(16, 0.0);
doubleloop.makeTAKE_PHOTO(17, 1.0);
doubleloop.makeSTOP(18, 0.0);
doubleloop.makeMANUAL_PID(19, 2.0, 70.0, -135.0);
doubleloop.makeMANUAL_PID(20, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(21, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeSTOP(22, 0.0);
doubleloop.makeMANUAL_PID(23, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(24, 0.0);
doubleloop.makeTAKE_PHOTO(25, 1.0);
doubleloop.makeSTOP(26, 0.0);
doubleloop.makeMANUAL_PID(27, 2.0, 70.0, -135.0);
doubleloop.makeMANUAL_PID(28, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(29, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeTRACE(30, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(31, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(32, 60.0, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeMANUAL_PID(33, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(34, 0.0);
doubleloop.makeTAKE_PHOTO(35, 1.0);
doubleloop.makeSTOP(36, 0.0);
doubleloop.makeMANUAL_PID(37, 2.0, 70.0, 135.0);
doubleloop.makeMANUAL_PID(38, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(39, 60.0, -0.57, 0.0, -0.32, 1.0);
doubleloop.makeSTOP(40, 0.0);
doubleloop.makeMANUAL_PID(41, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(42, 0.0);
doubleloop.makeTAKE_PHOTO(43, 1.0);
doubleloop.makeSTOP(44, 0.0);
doubleloop.makeMANUAL_PID(45, 2.0, 70.0, 135.0);
doubleloop.makeMANUAL_PID(46, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(47, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeSTOP(48, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(49, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(50, 2.0, 60.0, -90.0);
straight.makeMANUAL_PID(51, 1.0, 50.0, 50.0);
straight.makeSTOP(52, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(53, 2.0, 60.0, -90.0);
right.makeMANUAL_PID(54, 1.0, 50.0, 50.0);
right.makeSTOP(55, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(56, 2.0, 60.0, -90.0);
left.makeMANUAL_PID(57, 1.0, 50.0, 50.0);
left.makeSTOP(58, 0.0);
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