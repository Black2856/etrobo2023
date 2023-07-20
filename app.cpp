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
  clock.sleep(1000 * 1000 * 30);
  bool result;
  Manage_scenario manage_scenario;

  //#<make_scenario>
Manage_scene main("main");
main.makeTRACE(0, 10, -0.7, 0.0, 0.3);
main.makeTRACE(1, 70, -1.4, 0.0, 0.7);
main.makeTRACE(2, 40, -1.0, 0.0, 0.7);
main.makeTRACE(3, 15, -0.7, 0.0, 0.4);
main.makeCALL_SCENARIO("sub");
main.makeSTOP(4);
manage_scenario.add(main);

Manage_scene sub("sub");
sub.makeTRACE(5, 30.0, -0.7, 0.0, 0.3);
sub.makeSTOP(6);
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