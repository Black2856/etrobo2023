#include "app.h"
#include "Clock.h"
#include "section_core.h"
#include "sectionList.h"

using namespace ev3api;

static bool iscrunexeTerminate = false;
Clock clock;
SectionCore *sectionCore = new SectionCore(SectionList::Section00);

void *__dso_handle=0;

void order_task(intptr_t exinf) {
  if(iscrunexeTerminate == false){
    iscrunexeTerminate = sectionCore->run();
  }else{
    wup_tsk(MAIN_TASK);
  }
  ext_tsk();
}

void bluetooth_task(intptr_t exinf){
  ext_tsk();
}

void main_task(intptr_t unused) {

  sta_cyc(ORDER_CYC);
  sta_cyc(BLUETOOTH_CYC);
  
  slp_tsk(); //iscrunexeTerminate = true まで待機

  stp_cyc(ORDER_CYC);
  stp_cyc(BLUETOOTH_CYC);

  delete sectionCore;
  ext_tsk();
}
