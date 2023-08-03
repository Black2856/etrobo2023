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
main.makeCALL_SCENARIO("test");
main.makeCALL_SCENARIO("calibration");
main.makeCALL_SCENARIO("ready");
main.makeCALL_SCENARIO("run");
manage_scenario.add(main);

Manage_scene calibration("calibration");
calibration.makeMANUAL(0, 2, 50.0, 0.0);
calibration.makeCALIBRATION("record");
calibration.makeMANUAL(1, 2, -50.0, 0.0);
calibration.makeSTOP(2, 0);
calibration.makeCALIBRATION("stop");
calibration.makeON_LINE_MOVE(3, 10, 0.4, 0.0, 0.3);
calibration.makeSTOP(4, 0);
manage_scenario.add(calibration);

Manage_scene ready("ready");
ready.makeSTOP(5, 0.0);
manage_scenario.add(ready);

Manage_scene run("run");
run.makeTRACE(6, 80.0, 0.7, 0.0, 0.4, 1.0);
run.makeTRACE(7, 50.0, 0.4, 0.0, 0.2, 1.0);
run.makeSTOP(8, 1.0);
run.makeMANUAL(9, 2.0, 45.0, 0.0);
run.makeSTOP(10, 0.0);
manage_scenario.add(run);

Manage_scene test("test");
test.makeSTOP(11, 0.0);
test.makeMANUAL(12, 2.0, 40.0, 0.0);
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