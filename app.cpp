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
main.makeCALL_SCENARIO("goal");
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
run.makeTRACE(6, 85.0, -0.09, 0.0, -0.12, 0.3);
run.makeTRACE(7, 72.0, -0.45, 0.0, -0.35, 0.3);
run.makeTRACE(8, 60.0, -0.85, 0.0, -0.25, 0.3);
run.makeTRACE(9, 72.0, -0.45, 0.0, -0.35, 0.3);
run.makeTRACE(10, 80.0, -0.09, 0.0, -0.12, 0.3);
run.makeTRACE(11, 72.0, -0.45, 0.0, -0.25, 0.3);
run.makeTRACE(12, 60.0, -0.8, 0.0, -0.45, 0.3);
run.makeSTOP(13, 0.1);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(14, 75, 0.6, 0.0, 0.4, 0.5);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(15, 70, -0.6, 0.0, -0.4, 1.0);
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(16, 70, 0.6, 0.0, 0.4, 1.0);
doubleloop.makeSTOP(17, 0);
doubleloop.makeMANUAL_PID(18, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(19, 1);
doubleloop.makeMANUAL_PID(20, 2, 80.0, -120.0);
doubleloop.makeMANUAL_PID(21, 5, -80.0, 1.0);
doubleloop.makeTRACE(22, 75, 0.9, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(23, 0);
doubleloop.makeMANUAL_PID(24, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(25, 1);
doubleloop.makeMANUAL_PID(26, 2, 80.0, -130.0);
doubleloop.makeMANUAL_PID(27, 5, -80.0, 1.0);
doubleloop.makeTRACE(28, 75, 0.8, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(29, 0);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(30, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(31, 0);
doubleloop.makeMANUAL_PID(32, 2, 80.0, -90.0);
doubleloop.makeTAKE_PHOTO(33, 1);
doubleloop.makeMANUAL_PID(34, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(35, 5, 80.0, 1.0);
doubleloop.makeTRACE(36, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(37, 0);
doubleloop.makeMANUAL_PID(38, 2, 60.0, -90.0);
doubleloop.makeTAKE_PHOTO(39, 1);
doubleloop.makeMANUAL_PID(40, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(41, 5, 80.0, 1.0);
doubleloop.makeTRACE(42, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(43, 2, 80.0, -55.0);
doubleloop.makeTRACE(44, 55, -0.47, 0.0, -0.55, 0.5);
doubleloop.makeTRACE(45, 65, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(46, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(47, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(48, 1.0, 75.0, 360.0);
straight.makeSTOP(49, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(50, 2.0, 80.0, -90.0);
right.makeSTOP(51, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(52, 2.0, 80.0, 90.0);
left.makeSTOP(53, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(54, 60, 0.6, 0.0, 0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(55, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(56, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(57, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(58, 1, 65.0, 35.0);
whileRun.makeSTOP(59, 0);
whileRun.makeMANUAL_PID(60, 2, 80.0, -90.0);
whileRun.makeSTOP(61, 0);
whileRun.makeMANUAL_PID(62, 1, 65.0, 565.0);
whileRun.makeSTOP(63, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeSTOP(64, 0.0);
LtoR.makeMANUAL_PID(65, 4.0, 80.0, -45.0);
LtoR.makeSTOP(66, 0.0);
LtoR.makeMANUAL_PID(67, 3.0, 80.0, 40.0);
LtoR.makeSTOP(68, 0.0);
LtoR.makeMANUAL_PID(69, 5.0, -65.0, 1.0);
LtoR.makeSTOP(70, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeSTOP(71, 0.0);
RtoL.makeMANUAL_PID(72, 3.0, 80.0, 45.0);
RtoL.makeSTOP(73, 0.0);
RtoL.makeMANUAL_PID(74, 4.0, 80.0, -40.0);
RtoL.makeSTOP(75, 0.0);
RtoL.makeMANUAL_PID(76, 5.0, 65.0, 1.0);
RtoL.makeSTOP(77, 0.0);
manage_scenario.add(RtoL);

Manage_scene goal("goal");
goal.makeMANUAL(78, 1.0, 70.0, 0.5);
goal.makeMANUAL_PID(79, 1.0, 70.0, 20.0);
goal.makeSTOP(80, 0.0);
goal.makeMANUAL_PID(81, 5.0, -80.0, 1.0);
goal.makeSTOP(82, 0.0);
goal.makeTRACE(83, 85.0, 0.09, 0.0, 0.12, 0.3);
goal.makeSTOP(84, 0.0);
manage_scenario.add(goal);

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