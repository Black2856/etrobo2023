#include "app.h"

#include "setting.h"
#include "Motor.h"
#include "Clock.h"
#include "arg_info.h"
#include "manage_scenario.h"
#include "manage_scene.h"
#include "Judge.h"
#include "unit.h"
#include <functional>
#include <memory>

using namespace ev3api;

class Walker {
public:
  void run();
  
  JudgeMileage mileage;
  JudgeSonar sonar;
  JudgeTime time;
  JudgeAngle angle;
  unit::judge j = {&mileage, &sonar, &time, &angle};
  std::function<int(int)> b;
private:
  Clock clock;
};

void Walker::run() {
  
  TC_convert<bool (*)(unit::judge)> tc([](unit::judge j) {return false;});
  TC_convert<bool (*)(unit::judge)> aa = tc;
  aa.judge(j);

  bool result;
  Manage_scenario manage_scenario; //シナリオ管理のインスタンス
  Manage_scene main("main"); //シーン管理のインスタンス(シナリオ名は"main")
  main.makeTRACE([](unit::judge j) {return false;}, 20, -0.7, 0, 0.3); //シーンの作成
  manage_scenario.add(main); //シナリオ管理に作成したシナリオを追加
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