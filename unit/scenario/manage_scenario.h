/*
 * 作成日：2023/06/17
 * 作成者:船田
 */
#ifndef MANAGE_SCENARIO_H
#define MANAGE_SCENARIO_H

#include "manage_scene.h"

class Manage_scenario{
public:
    void add();
    void update();
    void execute();

private:
    uint16_t executeIdx;  

};

#endif