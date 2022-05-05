#pragma once

#include "calculator.h"

#include "GuilhermeCpu.h"
#include "GuilhermeDisplay.h"
#include "GuilhermeKeyboard.h"

class GuilhermeCalculator: public Calculator
{
    Cpu* cpu;
    Keyboard* keyboard;
    public:
    virtual void setDisplay(Display* );
    virtual void setCpu(Cpu* );
    virtual void setKeyboard(Keyboard* );
};