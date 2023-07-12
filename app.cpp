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
  Manage_scenario manage_scenario; //シナリオ管理のインスタンス

  //#<make_scenario>
Manage_scene main("main")
main.makeTRACE(0, 23, 23.0, 11.0, 32.5)
main.makeMANUAL(1, 1, 30.0)
main.makeCALL_SCENARIO("sub")
main.makeSTOP(2)
main.makeTRACE(3, 4, 5.0, 2.0, 1.0)
manage_scenario.add(main)

Manage_scene sub("sub")
sub.makeMANUAL(4, 2.0, 13.0)
sub.makeTRACE(5, 2.0, 3.0, 4.0, 5.0)
sub.makeSTOP(6)
manage_scenario.add(sub)

  //#</make_scenario>

  manage_scenario.update(); //シナリオのコンパイルを行う

  while(1) {
    result = manage_scenario.execute(); //シナリオの実行　全ての遷移が終わるとtrueが返る
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