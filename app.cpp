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
run.makeTRACE(6, 50.0, 0.4, 0.0, 0.5, 0.5);
run.makeMANUAL_PID(7, 2.0, 80.0, 80.0);
run.makeMANUAL_PID(8, 5.0, -80.0, 1.0);
run.makeTRACE(9, 50.0, 0.4, 0.0, 0.5, 0.5);
run.makeMANUAL_PID(10, 2.0, 80.0, 80.0);
run.makeMANUAL_PID(11, 5.0, -80.0, 1.0);
run.makeTRACE(12, 50.0, 0.4, 0.0, 0.5, 0.5);
run.makeMANUAL_PID(13, 2.0, 80.0, 80.0);
run.makeMANUAL_PID(14, 5.0, -80.0, 1.0);
run.makeTRACE(15, 50.0, 0.4, 0.0, 0.5, 0.5);
run.makeMANUAL_PID(16, 2.0, 80.0, 80.0);
run.makeMANUAL_PID(17, 5.0, -80.0, 1.0);
run.makeSTOP(18, 0.0);
manage_scenario.add(run);

Manage_scene doubleloop("doubleloop");
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(19, 75, 0.6, 0.0, 0.4, 0.5);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(20, 70, -0.6, 0.0, -0.4, 1.0);
doubleloop.makeCALL_SCENARIO("LtoR");
doubleloop.makeTRACE(21, 70, 0.6, 0.0, 0.4, 1.0);
doubleloop.makeSTOP(22, 0);
doubleloop.makeMANUAL_PID(23, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(24, 1);
doubleloop.makeSTOP(25, 0);
doubleloop.makeMANUAL_PID(26, 2, 80.0, -120.0);
doubleloop.makeMANUAL_PID(27, 5, -80.0, 1.0);
doubleloop.makeTRACE(28, 75, 0.9, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(29, 0);
doubleloop.makeMANUAL_PID(30, 2, 80.0, 90.0);
doubleloop.makeTAKE_PHOTO(31, 1);
doubleloop.makeMANUAL_PID(32, 2, 80.0, -130.0);
doubleloop.makeMANUAL_PID(33, 5, -80.0, 1.0);
doubleloop.makeTRACE(34, 75, 0.8, 0.0, 0.7, 1.0);
doubleloop.makeSTOP(35, 0);
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(36, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(37, 0);
doubleloop.makeMANUAL_PID(38, 2, 80.0, -90.0);
doubleloop.makeTAKE_PHOTO(39, 1);
doubleloop.makeSTOP(40, 0);
doubleloop.makeMANUAL_PID(41, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(42, 5, 80.0, 1.0);
doubleloop.makeTRACE(43, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeSTOP(44, 0);
doubleloop.makeMANUAL_PID(45, 2, 60.0, -90.0);
doubleloop.makeTAKE_PHOTO(46, 1);
doubleloop.makeMANUAL_PID(47, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(48, 5, 80.0, 1.0);
doubleloop.makeTRACE(49, 70, -0.85, 0.0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(50, 2, 80.0, -55.0);
doubleloop.makeTRACE(51, 55, -0.47, 0.0, -0.55, 0.5);
doubleloop.makeTRACE(52, 65, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(53, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(54, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(55, 1.0, 55.0, 360.0);
straight.makeSTOP(56, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(57, 2.0, 80.0, -90.0);
right.makeSTOP(58, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(59, 2.0, 80.0, 90.0);
left.makeSTOP(60, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(61, 60, 0.6, 0.0, 0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(62, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(63, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(64, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(65, 1, 65.0, 35.0);
whileRun.makeSTOP(66, 0);
whileRun.makeMANUAL_PID(67, 2, 80.0, -90.0);
whileRun.makeSTOP(68, 0);
whileRun.makeMANUAL_PID(69, 1, 65.0, 565.0);
whileRun.makeSTOP(70, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeSTOP(71, 0.0);
LtoR.makeMANUAL_PID(72, 4.0, 80.0, -45.0);
LtoR.makeSTOP(73, 0.0);
LtoR.makeMANUAL_PID(74, 3.0, 80.0, 40.0);
LtoR.makeSTOP(75, 0.0);
LtoR.makeMANUAL_PID(76, 5.0, -65.0, 1.0);
LtoR.makeSTOP(77, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeSTOP(78, 0.0);
RtoL.makeMANUAL_PID(79, 3.0, 80.0, 45.0);
RtoL.makeSTOP(80, 0.0);
RtoL.makeMANUAL_PID(81, 4.0, 80.0, -40.0);
RtoL.makeSTOP(82, 0.0);
RtoL.makeMANUAL_PID(83, 5.0, 65.0, 1.0);
RtoL.makeSTOP(84, 0.0);
manage_scenario.add(RtoL);

Manage_scene goal("goal");
goal.makeMANUAL(85, 1.0, 60.0, 0.5);
goal.makeMANUAL_PID(86, 1.0, 60.0, 20.0);
goal.makeSTOP(87, 0.0);
goal.makeMANUAL_PID(88, 2.0, 80.0, 50.0);
goal.makeMANUAL_PID(89, 5.0, -80.0, 1.0);
goal.makeSTOP(90, 0.0);
goal.makeTRACE(91, 55.0, 0.09, 0.0, 0.12, 0.3);
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