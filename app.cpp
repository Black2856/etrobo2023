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
run.makeTRACE(7, 60.0, -0.09, 0.0, -0.12, 0.2);
run.makeTRACE(8, 60.0, -0.85, 0.0, -0.5, 0.3);
run.makeTRACE(9, 85.0, -0.45, 0.0, -0.25, 0.2);
run.makeTRACE(10, 85.0, -0.1, 0.0, -0.12, 0.3);
run.makeTRACE(11, 60.0, -0.1, 0.0, -0.12, 0.2);
run.makeTRACE(12, 60.0, -0.8, 0.0, -0.5, 0.3);
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
doubleloop.makeCALL_SCENARIO("RtoL");
doubleloop.makeTRACE(30, 55, -0.3, 0.0, -0.12, 0.3);
doubleloop.makeTRACE(31, 55, -0.3, 0.0, -0.12, 0.3);
doubleloop.makeSTOP(32, 0);
doubleloop.makeMANUAL_PID(33, 1, 60.0, 20.0);
doubleloop.makeMANUAL_PID(34, 5, 80.0, 1.0);
doubleloop.makeTRACE(35, 60, -0.85, 0.0, -0.8, 0.5);
doubleloop.makeSTOP(36, 0);
doubleloop.makeMANUAL_PID(37, 2, 80.0, -90.0);
doubleloop.makeTAKE_PHOTO(38, 1);
doubleloop.makeSTOP(39, 0);
doubleloop.makeMANUAL_PID(40, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(41, 5, 80.0, 1.0);
doubleloop.makeTRACE(42, 70, -1.0, 0.0, -1.0, 1.0);
doubleloop.makeSTOP(43, 0);
doubleloop.makeMANUAL_PID(44, 2, 60.0, -90.0);
doubleloop.makeTAKE_PHOTO(45, 1);
doubleloop.makeMANUAL_PID(46, 2, 80.0, 130.0);
doubleloop.makeMANUAL_PID(47, 5, 80.0, 1.0);
doubleloop.makeTRACE(48, 70, -1.0, 0.0, -1.0, 1.0);
doubleloop.makeTRACE(49, 70, -1.0, 0.0, -1.0, 1.0);
doubleloop.makeMANUAL_PID(50, 2, 80.0, -60.0);
doubleloop.makeTRACE(51, 50, -0.47, 0.0, -0.55, 0.5);
doubleloop.makeSTOP(52, 0);
doubleloop.makeMANUAL_PID(53, 2, 80.0, 90.0);
doubleloop.makeMANUAL_PID(54, 5, 80.0, 1.0);
doubleloop.makeTRACE(55, 55, -1.0, 0.0, -1.0, 0.4);
doubleloop.makeSTOP(56, 0);
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(57, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeTRACE(58, 50.0, 0.4, 0.0, 0.6, 0.5);
straight.makeSTOP(59, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(60, 2.0, 80.0, -80.0);
right.makeMANUAL_PID(61, 5.0, 80.0, 1.0);
right.makeSTOP(62, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(63, 2.0, 80.0, 80.0);
left.makeMANUAL_PID(64, 5.0, -80.0, 1.0);
left.makeSTOP(65, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeCALL_SCENARIO("LtoR");
whileRun.makeTRACE(66, 60, 0.6, 0.0, 0.7, 0.5);
whileRun.makeCALL_SCENARIO("RtoL");
whileRun.makeTRACE(67, 65, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(68, 80, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(69, 60, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(70, 1, 65.0, 35.0);
whileRun.makeSTOP(71, 0);
whileRun.makeMANUAL_PID(72, 2, 80.0, -90.0);
whileRun.makeSTOP(73, 0);
whileRun.makeMANUAL_PID(74, 1, 65.0, 565.0);
whileRun.makeSTOP(75, 0);
manage_scenario.add(whileRun);

Manage_scene LtoR("LtoR");
LtoR.makeSTOP(76, 0.0);
LtoR.makeMANUAL_PID(77, 4.0, 80.0, -45.0);
LtoR.makeSTOP(78, 0.0);
LtoR.makeMANUAL_PID(79, 3.0, 80.0, 40.0);
LtoR.makeSTOP(80, 0.0);
LtoR.makeMANUAL_PID(81, 5.0, -65.0, 1.0);
LtoR.makeSTOP(82, 0.0);
manage_scenario.add(LtoR);

Manage_scene RtoL("RtoL");
RtoL.makeSTOP(83, 0.0);
RtoL.makeMANUAL_PID(84, 3.0, 80.0, 45.0);
RtoL.makeSTOP(85, 0.0);
RtoL.makeMANUAL_PID(86, 4.0, 80.0, -40.0);
RtoL.makeSTOP(87, 0.0);
RtoL.makeMANUAL_PID(88, 5.0, 65.0, 1.0);
RtoL.makeSTOP(89, 0.0);
manage_scenario.add(RtoL);

Manage_scene goal("goal");
goal.makeMANUAL(90, 1.0, 70.0, 0.5);
goal.makeMANUAL_PID(91, 1.0, 70.0, 20.0);
goal.makeSTOP(92, 0.0);
goal.makeMANUAL_PID(93, 2.0, 80.0, 80.0);
goal.makeMANUAL_PID(94, 5.0, -80.0, 1.0);
goal.makeSTOP(95, 0.0);
goal.makeTRACE(96, 55.0, 0.15, 0.0, 0.2, 0.3);
goal.makeTRACE(97, 55.0, 0.15, 0.0, 0.2, 0.3);
goal.makeSTOP(98, 0.0);
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