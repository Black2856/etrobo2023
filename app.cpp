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
run.makeTRACE(6, 85.0, -0.09, 0.0, -0.12, 0.5);
run.makeTRACE(7, 60.0, -0.75, 0.0, -0.8, 0.4);
run.makeTRACE(8, 80.0, -0.09, 0.0, -0.12, 0.5);
run.makeTRACE(9, 60.0, -0.75, 0.0, -0.6, 0.4);
run.makeSTOP(10, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(11, 75, 0.6, 0.0, 0.4, 0.5);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(12, 70, -0.6, 0.0, -0.4, 1.0);
doubleloop.makeSTOP(13, 0);
doubleloop.makeMANUAL_PID(14, 2, 80.0, 100.0);
doubleloop.makeSTOP(15, 0);
doubleloop.makeTAKE_PHOTO(16, 1);
doubleloop.makeSTOP(17, 0);
doubleloop.makeMANUAL_PID(18, 2, 80.0, -120.0);
doubleloop.makeMANUAL_PID(19, 5, -80.0, 1.0);
doubleloop.makeTRACE(20, 75, 0.9, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(21, 0);
doubleloop.makeMANUAL_PID(22, 2, 80.0, 130.0);
doubleloop.makeSTOP(23, 0);
doubleloop.makeTAKE_PHOTO(24, 1);
doubleloop.makeSTOP(25, 0);
doubleloop.makeMANUAL_PID(26, 2, 80.0, -130.0);
doubleloop.makeMANUAL_PID(27, 5, -80.0, 1.0);
doubleloop.makeTRACE(28, 75, 0.8, 0.0, 0.7, 1.0);
doubleloop.makeTRACE(29, 75, 0.8, 0.0, 0.7, 0.5);
doubleloop.makeMANUAL_PID(30, 2, 60.0, 15.0);
doubleloop.makeMANUAL_PID(31, 5, -60.0, 1.0);
doubleloop.makeTRACE(32, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(33, 0);
doubleloop.makeMANUAL_PID(34, 2, 80.0, -100.0);
doubleloop.makeSTOP(35, 0);
doubleloop.makeTAKE_PHOTO(36, 1);
doubleloop.makeSTOP(37, 0);
doubleloop.makeMANUAL_PID(38, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(39, 5, 80.0, 1.0);
doubleloop.makeTRACE(40, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(41, 0);
doubleloop.makeMANUAL_PID(42, 2, 60.0, -100.0);
doubleloop.makeSTOP(43, 0);
doubleloop.makeTAKE_PHOTO(44, 1);
doubleloop.makeSTOP(45, 0);
doubleloop.makeMANUAL_PID(46, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(47, 5, 80.0, 1.0);
doubleloop.makeTRACE(48, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(49, 2, 65.0, -30.0);
doubleloop.makeTRACE(50, 55, -0.12, 0.0, -0.1, 0.5);
doubleloop.makeTRACE(51, 65, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(52, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(53, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(54, 1.0, 60.0, 350.0);
straight.makeSTOP(55, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(56, 2.0, 60.0, -90.0);
right.makeSTOP(57, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(58, 2.0, 60.0, 90.0);
left.makeSTOP(59, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(60, 60, 0.6, 0.0, -0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(61, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(62, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(63, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(64, 1, 65.0, 100.0);
whileRun.makeSTOP(65, 0);
whileRun.makeMANUAL_PID(66, 2, 80.0, -90.0);
whileRun.makeSTOP(67, 0);
whileRun.makeMANUAL_PID(68, 1, 65.0, 550.0);
whileRun.makeSTOP(69, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeMANUAL_PID(70, 4.0, 80.0, -35.0);
LtoR.makeMANUAL_PID(71, 3.0, 80.0, 35.0);
LtoR.makeMANUAL_PID(72, 5.0, 65.0, 1.0);
LtoR.makeSTOP(73, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeMANUAL_PID(74, 3.0, 80.0, 35.0);
RtoL.makeMANUAL_PID(75, 4.0, 80.0, -35.0);
RtoL.makeMANUAL_PID(76, 5.0, -65.0, 1.0);
RtoL.makeSTOP(77, 0.0);
manage_scenario.add(RtoL);

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