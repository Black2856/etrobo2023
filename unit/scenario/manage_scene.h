/*
 * 作成日:2023/06/17
 * 作成者:船田
 */
#ifndef MANAGE_SCENE_H
#define MANAGE_SCENE_H

#include "scene.h"
#include <initializer_list>

class Manage_scene{
public:
    Manage_scene(const std::string scenarioName);

    void makeCALL_SCENARIO();
    void makeTRACE();
    void makeSTOP();
    void makeMANUAL();

private:
    std::string scenarioName;
    std::vector<Scene> scenario;
}

#endif