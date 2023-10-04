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
doubleloop.makeMANUAL_PID(11, 2.0, 65.0, -45);
doubleloop.makeMANUAL_PID(12, 5.0, -65.0, 1);
doubleloop.makeTRACE(13, 75.0, 0.6, 0, 0.4, 0.5);
doubleloop.makeMANUAL_PID(14, 2.0, 65.0, 45);
doubleloop.makeMANUAL_PID(15, 5.0, 65.0, 1);
doubleloop.makeTRACE(16, 75.0, -0.6, 0, -0.4, 0.5);
doubleloop.makeSTOP(17, 0.0);
doubleloop.makeMANUAL_PID(18, 2.0, 80.0, 100);
doubleloop.makeSTOP(19, 0.0);
doubleloop.makeTAKE_PHOTO(20, 1.0);
doubleloop.makeSTOP(21, 0.0);
doubleloop.makeMANUAL_PID(22, 2.0, 80.0, -120);
doubleloop.makeMANUAL_PID(23, 5.0, -80.0, 1);
doubleloop.makeTRACE(24, 75.0, 0.9, 0, 0.7, 1.0);
doubleloop.makeSTOP(25, 0.0);
doubleloop.makeMANUAL_PID(26, 2.0, 80.0, 130);
doubleloop.makeSTOP(27, 0.0);
doubleloop.makeTAKE_PHOTO(28, 1.0);
doubleloop.makeSTOP(29, 0.0);
doubleloop.makeMANUAL_PID(30, 2.0, 80.0, -130);
doubleloop.makeMANUAL_PID(31, 5.0, -80.0, 1);
doubleloop.makeTRACE(32, 75.0, 0.8, 0, 0.7, 1.0);
doubleloop.makeTRACE(33, 75.0, 0.8, 0, 0.7, 0.5);
doubleloop.makeMANUAL_PID(34, 2.0, 60.0, 15);
doubleloop.makeTRACE(35, 60.0, -0.85, 0, -0.8, 0.5);
doubleloop.makeSTOP(36, 0.0);
doubleloop.makeMANUAL_PID(37, 2.0, 80.0, -100);
doubleloop.makeSTOP(38, 0.0);
doubleloop.makeTAKE_PHOTO(39, 1.0);
doubleloop.makeSTOP(40, 0.0);
doubleloop.makeMANUAL_PID(41, 2.0, 80.0, 130);
doubleloop.makeMANUAL_PID(42, 5.0, 80.0, 1);
doubleloop.makeTRACE(43, 70.0, -0.85, 0, -0.8, 1.0);
doubleloop.makeSTOP(44, 0.0);
doubleloop.makeMANUAL_PID(45, 2.0, 60.0, -100);
doubleloop.makeSTOP(46, 0.0);
doubleloop.makeTAKE_PHOTO(47, 1.0);
doubleloop.makeSTOP(48, 0.0);
doubleloop.makeMANUAL_PID(49, 2.0, 80.0, 130);
doubleloop.makeMANUAL_PID(50, 5.0, 80.0, 1);
doubleloop.makeTRACE(51, 70.0, -0.85, 0, -0.8, 1.0);
doubleloop.makeMANUAL_PID(52, 2.0, 65.0, -30);
doubleloop.makeTRACE(53, 55.0, -0.12, 0, -0.1, 0.5);
doubleloop.makeTRACE(54, 65.0, -1.0, 0, -1.0, 0.4);
doubleloop.makeSTOP(55, 0.0);
doubleloop.makenan();
doubleloop.makenan( );
manage_scenario.add(doubleloop);

Manage_scene block("block");
block.makeSTOP(56, 0.0);
manage_scenario.add(block);

Manage_scene straight("straight");
straight.makeMANUAL_PID(57, 1.0, 60.0, 350.0);
straight.makeSTOP(58, 0.0);
manage_scenario.add(straight);

Manage_scene right("right");
right.makeMANUAL_PID(59, 2.0, 60.0, -90.0);
right.makeSTOP(60, 0.0);
manage_scenario.add(right);

Manage_scene left("left");
left.makeMANUAL_PID(61, 2.0, 60.0, 90.0);
left.makeSTOP(62, 0.0);
manage_scenario.add(left);

Manage_scene whileRun("whileRun");
whileRun.makeMANUAL_PID(63, 2.0, 65.0, -45.0);
whileRun.makeMANUAL_PID(64, 5.0, -65.0, 1.0);
whileRun.makeTRACE(65, 60.0, 0.6, 0.0, -0.7, 0.5);
whileRun.makeMANUAL_PID(66, 2.0, 60.0, 45.0);
whileRun.makeMANUAL_PID(67, 5.0, 65.0, 1.0);
whileRun.makeTRACE(68, 65.0, -1.0, 0.0, -1.0, 0.4);
whileRun.makeTRACE(69, 80.0, -0.12, 0.0, -0.1, 0.5);
whileRun.makeTRACE(70, 60.0, -0.12, 0.0, -0.1, 0.5);
whileRun.makeMANUAL_PID(71, 1.0, 65.0, 100.0);
whileRun.makeSTOP(72, 0.0);
whileRun.makeMANUAL_PID(73, 2.0, 80.0, -90.0);
whileRun.makeSTOP(74, 0.0);
whileRun.makeMANUAL_PID(75, 1.0, 65.0, 550.0);
whileRun.makeSTOP(76, 0.0);
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