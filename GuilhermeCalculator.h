#pragma once

#include "calculator.h"

#include "GuilhermeCpu.h"
#include "GuilhermeDisplay.h"
#include "GuilhermeKeyboard.h"

class GuilhermeCalculator: public Calculator
{
    Cpu* cpu;
    Keyboard* keyboard;
    Display* display;
    public:
    void setDisplay(Display* );
    void setCpu(Cpu* );
    void setKeyboard(Keyboard* );
    Display* getDisplay();
    Cpu* getCpu();
    Keyboard* getKeyboard();
};