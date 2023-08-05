#include "app.h"

#include "setting.h"
#include "Motor.h"
#include "Clock.h"
#include "arg_info.h"
#include "manage_scenario.h"
#include "manage_scene.h"
#include "Judge.h"
#include "Record.h"
#include "unit.h"

#include "functional"

using namespace ev3api;

class Walker {
public:
  void run();
private:
  Clock clock;
};

void Walker::run() {
  Record& record = Record::getInstance();

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
calibration.makeMANUAL_PID(1, 2, 50.0, -90.0);
calibration.makeSTOP(2, 0);
calibration.makeCALIBRATION("record");
calibration.makeMANUAL_PID(3, 2, 50.0, 540.0);
calibration.makeCALIBRATION("stop");
calibration.makeSTOP(4, 0);
calibration.makeMANUAL_PID(5, 5, 50.0, 1.0);
calibration.makeSTOP(6, 0);
manage_scenario.add(calibration);

Manage_scene ready("ready");
ready.makeSTOP(7, 0.0);
manage_scenario.add(ready);

Manage_scene run("run");
run.makeTRACE(8, 90.0, -0.06, 0.0, -0.15, 1.0);
run.makeTRACE(9, 50.0, -0.6, 0.0, -0.2, 0.5);
run.makeSTOP(10, 1.0);
manage_scenario.add(run);

Manage_scene test("test");
test.makeSTOP(11, 0.0);
test.makeMANUAL_PID(12, 1.0, 50.0, 3000.0);
test.makeSTOP(13, 0.0);
test.makeMANUAL_PID(14, 2.0, 50.0, 180.0);
test.makeSTOP(15, 0.0);
test.makeMANUAL_PID(16, 2.0, 50.0, -180.0);
test.makeSTOP(17, 0.0);
manage_scenario.add(test);

  //#</make_scenario>

  manage_scenario.update();

  while(1) {
    result = manage_scenario.execute();

    record.appendSensorData();

    clock.sleep(CYCLE);

    if (result == true) {
      break;
    }
  }
}

void main_task(intptr_t unused) {
  Walker walker;
  walker.run();
  ext_tsk();
}