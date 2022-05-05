#pragma once

#include "calculator.h"

#include "OurCpu.h"
#include "OurDisplay.h"
#include "OurKeyboard.h"

class OurCalculator: public Calculator
{
    Cpu* cpu;
    Keyboard* keyboard;
    public:
    virtual void setDisplay(Display* );
    virtual void setCpu(Cpu* );
    virtual void setKeyboard(Keyboard* );
};