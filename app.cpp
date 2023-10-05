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
doubleloop.makeSTOP(19, 0);
doubleloop.makeTAKE_PHOTO(20, 1);
doubleloop.makeSTOP(21, 0);
doubleloop.makeMANUAL_PID(22, 2, 80.0, -120.0);
doubleloop.makeMANUAL_PID(23, 5, -80.0, 1.0);
doubleloop.makeTRACE(24, 75, 0.9, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(25, 0);
doubleloop.makeMANUAL_PID(26, 2, 80.0, 90.0);
doubleloop.makeSTOP(27, 0);
doubleloop.makeTAKE_PHOTO(28, 1);
doubleloop.makeSTOP(29, 0);
doubleloop.makeMANUAL_PID(30, 2, 80.0, -130.0);
doubleloop.makeMANUAL_PID(31, 5, -80.0, 1.0);
doubleloop.makeTRACE(32, 75, 0.8, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(33, 0);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(34, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(35, 0);
doubleloop.makeMANUAL_PID(36, 2, 80.0, -90.0);
doubleloop.makeSTOP(37, 0);
doubleloop.makeTAKE_PHOTO(38, 1);
doubleloop.makeSTOP(39, 0);
doubleloop.makeMANUAL_PID(40, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(41, 5, 80.0, 1.0);
doubleloop.makeTRACE(42, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(43, 0);
doubleloop.makeMANUAL_PID(44, 2, 60.0, -90.0);
doubleloop.makeSTOP(45, 0);
doubleloop.makeTAKE_PHOTO(46, 1);
doubleloop.makeSTOP(47, 0);
doubleloop.makeMANUAL_PID(48, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(49, 5, 80.0, 1.0);
doubleloop.makeTRACE(50, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(51, 2, 80.0, -55.0);
doubleloop.makeTRACE(52, 55, -0.37, 0.0, -0.55, 0.5);
doubleloop.makeTRACE(53, 65, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(54, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(55, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(56, 1.0, 75.0, 360.0);
straight.makeSTOP(57, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(58, 2.0, 80.0, -90.0);
right.makeSTOP(59, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(60, 2.0, 80.0, 90.0);
left.makeSTOP(61, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(62, 60, 0.6, 0.0, 0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(63, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(64, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(65, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(66, 1, 65.0, 35.0);
whileRun.makeSTOP(67, 0);
whileRun.makeMANUAL_PID(68, 2, 80.0, -90.0);
whileRun.makeSTOP(69, 0);
whileRun.makeMANUAL_PID(70, 1, 65.0, 565.0);
whileRun.makeSTOP(71, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeSTOP(72, 0.0);
LtoR.makeMANUAL_PID(73, 4.0, 80.0, -45.0);
LtoR.makeSTOP(74, 0.0);
LtoR.makeMANUAL_PID(75, 3.0, 80.0, 40.0);
LtoR.makeSTOP(76, 0.0);
LtoR.makeMANUAL_PID(77, 5.0, -65.0, 1.0);
LtoR.makeSTOP(78, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeSTOP(79, 0.0);
RtoL.makeMANUAL_PID(80, 3.0, 80.0, 45.0);
RtoL.makeSTOP(81, 0.0);
RtoL.makeMANUAL_PID(82, 4.0, 80.0, -40.0);
RtoL.makeSTOP(83, 0.0);
RtoL.makeMANUAL_PID(84, 5.0, 65.0, 1.0);
RtoL.makeSTOP(85, 0.0);
manage_scenario.add(RtoL);

Manage_scene goal("goal");
goal.makeMANUAL(86, 1.0, 70.0, 0.5);
goal.makeMANUAL_PID(87, 1.0, 70.0, 20.0);
goal.makeSTOP(88, 0.0);
goal.makeMANUAL_PID(89, 5.0, -80.0, 1.0);
goal.makeSTOP(90, 0.0);
goal.makeTRACE(91, 85.0, -0.09, 0.0, -0.12, 0.3);
goal.makeSTOP(92, 0.0);
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