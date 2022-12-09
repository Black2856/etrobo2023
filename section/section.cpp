#include "section.h"

SectionList Section::running(const SectionList sectionID){
  this->currentSection = sectionID;
  if(sectionEntry == false){
    sectionEntry = true;
    clock.reset();
    entry();
  }
  main();
  condition();
  return this->currentSection;
}

void Section::transition(const SectionList sectionID){
  clock.reset();
  sectionEntry = false;
  this->currentSection = sectionID;
}