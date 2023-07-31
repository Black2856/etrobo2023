#include "app.h"

#include "setting.h"
#include "Motor.h"
#include "Clock.h"
#include "arg_info.h"
#include "manage_scenario.h"
#include "manage_scene.h"
#include "Judge.h"
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
  bool result;
  Manage_scenario manage_scenario;

  //#<make_scenario>
Manage_scene main("main");
main.makeSTOP(0, 0);
main.makeTRACE(1, 70, -1.4, 0.0, 0.7, 2.0);
main.makeTRACE(2, 10, -1.0, 0.0, 0.7, 0.5);
main.makeTRACE(3, 25, -0.7, 0.0, 0.4, 0.5);
main.makeCALL_SCENARIO("sub");
main.makeSTOP(4, 0.5);
manage_scenario.add(main);

Manage_scene sub("sub");
sub.makeTRACE(5, 20, -0.7, 0.0, 0.3, 0.0);
sub.makeMANUAL(6, 2, -10.0, 0.0);
sub.makeSTOP(7, 0);
sub.makeON_LINE_MOVE(8, 3, 0.4, 0.0, 0.3);
sub.makeCALIBRATION("record");
sub.makeSTOP(9, 0);
sub.makeCALIBRATION("stop");
manage_scenario.add(sub);

  //#</make_scenario>

  manage_scenario.update();

  while(1) {
    result = manage_scenario.execute();
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