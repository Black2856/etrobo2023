#include "app.h"

#include "setting.h"
#include "Clock.h"
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
main.makeCALL_SCENARIO("zero4");
manage_scenario.add(main);

Manage_scene calibration("calibration");
calibration.makeSTOP(0, 0);
calibration.makeMANUAL_PID(1, 2, 70.0, -90.0);
calibration.makeSTOP(2, 0);
calibration.makeCALIBRATION("record");
calibration.makeMANUAL_PID(3, 2, 70.0, 540.0);
calibration.makeCALIBRATION("stop");
calibration.makeSTOP(4, 0);
calibration.makeMANUAL_PID(5, 5, 70.0, 1.0);
calibration.makeSTOP(6, 0);
manage_scenario.add(calibration);

Manage_scene ready("ready");
ready.makeSTOP(7, 0.0);
manage_scenario.add(ready);

Manage_scene run("run");
run.makeTRACE(8, 90.0, -0.055, 0.0, -0.07, 0.5);
run.makeTRACE(9, 65.0, -0.8, 0.0, -0.3, 0.4);
run.makeTRACE(10, 90.0, -0.055, 0.0, -0.07, 0.5);
run.makeTRACE(11, 65.0, -0.8, 0.0, -0.3, 0.4);
run.makeSTOP(12, 1.0);
manage_scenario.add(run);

Manage_scene zero4("zero4");
zero4.makeSTOP(13, 0.0);
zero4.makeMANUAL_PID(14, 1.0, 90.0, 4000.0);
zero4.makeSTOP(15, 0.0);
manage_scenario.add(zero4);

Manage_scene test("test");
test.makeSTOP(16, 0.0);
manage_scenario.add(test);

Manage_scene turn("turn");
turn.makeMANUAL_PID(17, 2.0, 60.0, -90.0);
turn.makeMANUAL(18, 1.0, 60.0, 0.0);
turn.makeSTOP(19, 0.0);
manage_scenario.add(turn);

    //#</make_scenario>

    this->manage_scenario = &manage_scenario;
    this->manage_scenario->update();

    while(1) {
        result = this->manage_scenario->execute();
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