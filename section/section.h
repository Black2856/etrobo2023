#ifndef SECTION_H
#include "stdint.h"
#include "Clock.h"
#include "dataIO.h"
#include "sectionList.h"

using namespace ev3api;

class Section{// >〇<は継承先で設定する
public:
  SectionList running(SectionList currentSection); //区画の実行
  virtual void main() = 0; //区画の内容の実行　>〇<
protected:
  DataIO *dataIO = DataIO::getInstance();

  virtual void entry() = 0; //区画遷移時の初期化 >〇<
  virtual void condition() = 0; //区画遷移条件 >〇<
  void transition(const SectionList sectionID); //区画遷移処理

  bool sectionEntry = false; //区画遷移したかのフラグ
  SectionList currentSection; //現在の区画番号
  static const SectionList section; //自身の区画番号
  Clock clock; //区画遷移の時間管理
};

#define SECTION_H
#endif