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
doubleloop.makeSTOP(20, 0);
doubleloop.makeMANUAL_PID(21, 2, 80.0, -120.0);
doubleloop.makeMANUAL_PID(22, 5, -80.0, 1.0);
doubleloop.makeTRACE(23, 75, 0.9, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(24, 0);
doubleloop.makeMANUAL_PID(25, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(26, 1);
doubleloop.makeMANUAL_PID(27, 2, 80.0, -130.0);
doubleloop.makeMANUAL_PID(28, 5, -80.0, 1.0);
doubleloop.makeTRACE(29, 75, 0.8, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(30, 0);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(31, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(32, 0);
doubleloop.makeMANUAL_PID(33, 2, 80.0, -90.0);
doubleloop.makeTAKE_PHOTO(34, 1);
doubleloop.makeSTOP(35, 0);
doubleloop.makeMANUAL_PID(36, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(37, 5, 80.0, 1.0);
doubleloop.makeTRACE(38, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(39, 0);
doubleloop.makeMANUAL_PID(40, 2, 60.0, -90.0);
doubleloop.makeTAKE_PHOTO(41, 1);
doubleloop.makeMANUAL_PID(42, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(43, 5, 80.0, 1.0);
doubleloop.makeTRACE(44, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(45, 2, 80.0, -55.0);
doubleloop.makeTRACE(46, 55, -0.47, 0.0, -0.55, 0.5);
doubleloop.makeTRACE(47, 65, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(48, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(49, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeTRACE(50, 50.0, 0.4, 0.0, 0.6, 0.5);
straight.makeSTOP(51, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(52, 2.0, 80.0, -80.0);
right.makeMANUAL_PID(53, 5.0, 80.0, 1.0);
right.makeSTOP(54, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(55, 2.0, 80.0, 80.0);
left.makeMANUAL_PID(56, 5.0, -80.0, 1.0);
left.makeSTOP(57, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(58, 60, 0.6, 0.0, 0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(59, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(60, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(61, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(62, 1, 65.0, 35.0);
whileRun.makeSTOP(63, 0);
whileRun.makeMANUAL_PID(64, 2, 80.0, -90.0);
whileRun.makeSTOP(65, 0);
whileRun.makeMANUAL_PID(66, 1, 65.0, 565.0);
whileRun.makeSTOP(67, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeSTOP(68, 0.0);
LtoR.makeMANUAL_PID(69, 4.0, 80.0, -45.0);
LtoR.makeSTOP(70, 0.0);
LtoR.makeMANUAL_PID(71, 3.0, 80.0, 40.0);
LtoR.makeSTOP(72, 0.0);
LtoR.makeMANUAL_PID(73, 5.0, -65.0, 1.0);
LtoR.makeSTOP(74, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeSTOP(75, 0.0);
RtoL.makeMANUAL_PID(76, 3.0, 80.0, 45.0);
RtoL.makeSTOP(77, 0.0);
RtoL.makeMANUAL_PID(78, 4.0, 80.0, -40.0);
RtoL.makeSTOP(79, 0.0);
RtoL.makeMANUAL_PID(80, 5.0, 65.0, 1.0);
RtoL.makeSTOP(81, 0.0);
manage_scenario.add(RtoL);

Manage_scene goal("goal");
goal.makeMANUAL(82, 1.0, 70.0, 0.5);
goal.makeMANUAL_PID(83, 1.0, 70.0, 20.0);
goal.makeSTOP(84, 0.0);
goal.makeMANUAL_PID(85, 2.0, 80.0, 80.0);
goal.makeMANUAL_PID(86, 5.0, -80.0, 1.0);
goal.makeSTOP(87, 0.0);
goal.makeTRACE(88, 55.0, 0.15, 0.0, 0.2, 0.3);
goal.makeTRACE(89, 55.0, 0.15, 0.0, 0.2, 0.3);
goal.makeSTOP(90, 0.0);
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