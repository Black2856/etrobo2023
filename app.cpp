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
run.makeMANUAL_PID(6, 1.0, 55.0, 360.0);
run.makeMANUAL_PID(7, 2.0, 80.0, 90.0);
run.makeMANUAL_PID(8, 1.0, 55.0, 360.0);
run.makeMANUAL_PID(9, 2.0, 80.0, 90.0);
run.makeMANUAL_PID(10, 1.0, 55.0, 360.0);
run.makeMANUAL_PID(11, 2.0, 80.0, 90.0);
run.makeMANUAL_PID(12, 1.0, 55.0, 360.0);
run.makeMANUAL_PID(13, 2.0, 80.0, 90.0);
run.makeSTOP(14, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(15, 75, 0.6, 0.0, 0.4, 0.5);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(16, 70, -0.6, 0.0, -0.4, 1.0);
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(17, 70, 0.6, 0.0, 0.4, 1.0);
doubleloop.makeSTOP(18, 0);
doubleloop.makeMANUAL_PID(19, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(20, 1);
doubleloop.makeSTOP(21, 0);
doubleloop.makeMANUAL_PID(22, 2, 80.0, -120.0);
doubleloop.makeMANUAL_PID(23, 5, -80.0, 1.0);
doubleloop.makeTRACE(24, 75, 0.9, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(25, 0);
doubleloop.makeMANUAL_PID(26, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(27, 1);
doubleloop.makeMANUAL_PID(28, 2, 80.0, -130.0);
doubleloop.makeMANUAL_PID(29, 5, -80.0, 1.0);
doubleloop.makeTRACE(30, 75, 0.8, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(31, 0);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(32, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(33, 0);
doubleloop.makeMANUAL_PID(34, 2, 80.0, -90.0);
doubleloop.makeTAKE_PHOTO(35, 1);
doubleloop.makeSTOP(36, 0);
doubleloop.makeMANUAL_PID(37, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(38, 5, 80.0, 1.0);
doubleloop.makeTRACE(39, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(40, 0);
doubleloop.makeMANUAL_PID(41, 2, 60.0, -90.0);
doubleloop.makeTAKE_PHOTO(42, 1);
doubleloop.makeMANUAL_PID(43, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(44, 5, 80.0, 1.0);
doubleloop.makeTRACE(45, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(46, 2, 80.0, -55.0);
doubleloop.makeTRACE(47, 55, -0.47, 0.0, -0.55, 0.5);
doubleloop.makeTRACE(48, 65, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(49, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(50, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(51, 1.0, 55.0, 360.0);
straight.makeSTOP(52, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(53, 2.0, 80.0, -90.0);
right.makeSTOP(54, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(55, 2.0, 80.0, 90.0);
left.makeSTOP(56, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(57, 60, 0.6, 0.0, 0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(58, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(59, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(60, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(61, 1, 65.0, 35.0);
whileRun.makeSTOP(62, 0);
whileRun.makeMANUAL_PID(63, 2, 80.0, -90.0);
whileRun.makeSTOP(64, 0);
whileRun.makeMANUAL_PID(65, 1, 65.0, 565.0);
whileRun.makeSTOP(66, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeSTOP(67, 0.0);
LtoR.makeMANUAL_PID(68, 4.0, 80.0, -45.0);
LtoR.makeSTOP(69, 0.0);
LtoR.makeMANUAL_PID(70, 3.0, 80.0, 40.0);
LtoR.makeSTOP(71, 0.0);
LtoR.makeMANUAL_PID(72, 5.0, -65.0, 1.0);
LtoR.makeSTOP(73, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeSTOP(74, 0.0);
RtoL.makeMANUAL_PID(75, 3.0, 80.0, 45.0);
RtoL.makeSTOP(76, 0.0);
RtoL.makeMANUAL_PID(77, 4.0, 80.0, -40.0);
RtoL.makeSTOP(78, 0.0);
RtoL.makeMANUAL_PID(79, 5.0, 65.0, 1.0);
RtoL.makeSTOP(80, 0.0);
manage_scenario.add(RtoL);

Manage_scene goal("goal");
goal.makeMANUAL(81, 1.0, 60.0, 0.5);
goal.makeMANUAL_PID(82, 1.0, 60.0, 20.0);
goal.makeSTOP(83, 0.0);
goal.makeMANUAL_PID(84, 2.0, 80.0, 50.0);
goal.makeMANUAL_PID(85, 5.0, -80.0, 1.0);
goal.makeSTOP(86, 0.0);
goal.makeTRACE(87, 55.0, 0.09, 0.0, 0.12, 0.3);
goal.makeTRACE(88, 60.0, 0.09, 0.0, 0.12, 0.3);
goal.makeSTOP(89, 0.0);
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