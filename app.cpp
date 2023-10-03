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
main.makeCALL_SCENARIO("whileRun");
main.makeCALL_SCENARIO("block");
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
run.makeTRACE(6, 85.0, -0.08, 0.0, -0.1, 0.5);
run.makeTRACE(7, 60.0, -0.85, 0.0, -0.5, 0.4);
run.makeTRACE(8, 80.0, -0.08, 0.0, -0.1, 0.5);
run.makeTRACE(9, 60.0, -0.85, 0.0, -0.5, 0.4);
run.makeSTOP(10, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeMANUAL_PID(11, 2.0, 60.0, -15.0);
doubleloop.makeTRACE(12, 66.0, 0.57, 0.0, 0.4, 0.5);
doubleloop.makeMANUAL_PID(13, 2.0, 60.0, 10.0);
doubleloop.makeTRACE(14, 60.0, -0.57, 0.0, -0.32, 0.5);
doubleloop.makeSTOP(15, 0.0);
doubleloop.makeMANUAL_PID(16, 2.0, 60.0, 100.0);
doubleloop.makeSTOP(17, 0.0);
doubleloop.makeTAKE_PHOTO(18, 1.0);
doubleloop.makeSTOP(19, 0.0);
doubleloop.makeMANUAL_PID(20, 2.0, 60.0, -130.0);
doubleloop.makeMANUAL_PID(21, 5.0, -60.0, 1.0);
doubleloop.makeTRACE(22, 65.0, 0.6, 0.0, 0.5, 1.0);
doubleloop.makeSTOP(23, 0.0);
doubleloop.makeMANUAL_PID(24, 2.0, 60.0, 100.0);
doubleloop.makeSTOP(25, 0.0);
doubleloop.makeTAKE_PHOTO(26, 1.0);
doubleloop.makeSTOP(27, 0.0);
doubleloop.makeMANUAL_PID(28, 2.0, 60.0, -130.0);
doubleloop.makeMANUAL_PID(29, 5.0, -60.0, 1.0);
doubleloop.makeTRACE(30, 65.0, 0.6, 0.0, 0.5, 1.0);
doubleloop.makeTRACE(31, 65.0, 0.6, 0.0, 0.5, 0.5);
doubleloop.makeMANUAL_PID(32, 2.0, 60.0, 15.0);
doubleloop.makeTRACE(33, 60.0, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(34, 0.0);
doubleloop.makeMANUAL_PID(35, 2.0, 60.0, -100.0);
doubleloop.makeSTOP(36, 0.0);
doubleloop.makeTAKE_PHOTO(37, 1.0);
doubleloop.makeSTOP(38, 0.0);
doubleloop.makeMANUAL_PID(39, 2.0, 60.0, 130.0);
doubleloop.makeMANUAL_PID(40, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(41, 60.0, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(42, 0.0);
doubleloop.makeMANUAL_PID(43, 2.0, 60.0, -100.0);
doubleloop.makeSTOP(44, 0.0);
doubleloop.makeTAKE_PHOTO(45, 1.0);
doubleloop.makeSTOP(46, 0.0);
doubleloop.makeMANUAL_PID(47, 2.0, 60.0, 130.0);
doubleloop.makeMANUAL_PID(48, 5.0, 60.0, 1.0);
doubleloop.makeTRACE(49, 66.0, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(50, 2.0, 60.0, -55.0);
doubleloop.makeTRACE(51, 40.0, -0.12, 0.0, -0.1, 0.5);
doubleloop.makeTRACE(52, 65.0, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeMANUAL_PID(53, 2.0, 60.0, -15.0);
doubleloop.makeTRACE(54, 65.0, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeTRACE(55, 80.0, -0.12, 0.0, -0.1, 0.5);
doubleloop.makeTRACE(56, 40.0, -0.12, 0.0, -0.1, 0.5);
doubleloop.makeSTOP(57, 0.0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(58, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(59, 1.0, 60.0, 350.0);
straight.makeSTOP(60, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(61, 2.0, 60.0, -90.0);
right.makeSTOP(62, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(63, 2.0, 60.0, 90.0);
left.makeSTOP(64, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeMANUAL_PID(65, 1.0, 40.0, 100.0);
whileRun.makeMANUAL_PID(66, 2.0, 40.0, -90.0);
whileRun.makeMANUAL_PID(67, 1.0, 40.0, 1000.0);
whileRun.makeSTOP(68, 0.0);
manage_scenario.add(whileRun);

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