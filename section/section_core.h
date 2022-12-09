#ifndef SECTIONCORE_H
#include "stdint.h"
#include "run_area.h"
#include "section.h"
#include "curve.h"
#include "dataIO.h"
#include "ev3f.h"
#include "sectionList.h"

#include "ev3api.h"
#include "Clock.h"

class SectionCore{
public:
  SectionCore(const SectionList sectionID);//インスタンス時に実行する区画を入れる
  bool run();

private:
  DataIO *dataIO = DataIO::getInstance();
  EV3 *ev3 = EV3::getInstance();
  Clock clock;

  uint64_t pressed = 0;
  SectionList currentSection;
  bool terminate = false; //走行終了管理

  Section99 section99;
  Section00 section00;
  Section01 section01;
  Section02 section02;
  Section03 section03;
  Section04 section04;
  Section05 section05;
  Section06 section06;
  Section07 section07;
  Section08 section08;
  Section20 section20;
  Section21 section21;
  Section30 section30;
  Section31 section31;
  Section32 section32;
  Section33 section33;
  Section34 section34;
  Section35 section35;
  Section36 section36;
  Section37 section37;
  Section38 section38;
  Section39 section39;
  Section40 section40;
  Section41 section41;
  Section42 section42;
  Section43 section43;
  Section44 section44;
  Section80 section80;
  Section98 section98;
  Section *p_section[29] = {
    &section99,
    &section00,
    &section01,
    &section02,
    &section03,
    &section04,
    &section05,
    &section06,
    &section07,
    &section08,
    &section20,
    &section21,
    &section30,
    &section31,
    &section32,
    &section33,
    &section34,
    &section35,
    &section36,
    &section37,
    &section38,
    &section39,
    &section40,
    &section41,
    &section42,
    &section43,
    &section44,
    &section80,
    &section98
  };
};

#define SECTIONCORE_H
#endif