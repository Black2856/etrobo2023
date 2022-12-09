#include "control.h"

Control* Control::m_Control = NULL;

Control::Control(){}

Control::~Control(){}

Control* Control::getInstance(){
    if (m_Control == NULL){
        m_Control = new Control();
    }
    return m_Control;
}