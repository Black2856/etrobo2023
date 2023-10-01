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
doubleloop.makeTAKE_PHOTO(18, 1.0);
doubleloop.makeSTOP(19, 0.0);
doubleloop.makeMANUAL_PID(20, 2.0, 70.0, -135.0);
doubleloop.makeMANUAL_PID(21, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(22, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeSTOP(23, 0.0);
doubleloop.makeMANUAL_PID(24, 2.0, 60.0, 90.0);
doubleloop.makeSTOP(25, 0.0);
doubleloop.makeTAKE_PHOTO(26, 1.0);
doubleloop.makeSTOP(27, 0.0);
doubleloop.makeMANUAL_PID(28, 2.0, 70.0, -135.0);
doubleloop.makeMANUAL_PID(29, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(30, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeTRACE(31, 75.0, 0.57, 0.0, 0.32, 0.5);
doubleloop.makeMANUAL_PID(32, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(33, 60.0, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeMANUAL_PID(34, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(35, 0.0);
doubleloop.makeTAKE_PHOTO(36, 1.0);
doubleloop.makeSTOP(37, 0.0);
doubleloop.makeMANUAL_PID(38, 2.0, 70.0, 135.0);
doubleloop.makeMANUAL_PID(39, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(40, 60.0, -0.57, 0.0, -0.32, 1.0);
doubleloop.makeSTOP(41, 0.0);
doubleloop.makeMANUAL_PID(42, 2.0, 60.0, -90.0);
doubleloop.makeSTOP(43, 0.0);
doubleloop.makeTAKE_PHOTO(44, 1.0);
doubleloop.makeSTOP(45, 0.0);
doubleloop.makeMANUAL_PID(46, 2.0, 70.0, 135.0);
doubleloop.makeMANUAL_PID(47, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(48, 75.0, 0.57, 0.0, 0.32, 1.0);
doubleloop.makeSTOP(49, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(50, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(51, 2.0, 60.0, -90.0);
straight.makeMANUAL_PID(52, 1.0, 50.0, 50.0);
straight.makeSTOP(53, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(54, 2.0, 60.0, -90.0);
right.makeMANUAL_PID(55, 1.0, 50.0, 50.0);
right.makeSTOP(56, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(57, 2.0, 60.0, -90.0);
left.makeMANUAL_PID(58, 1.0, 50.0, 50.0);
left.makeSTOP(59, 0.0);
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