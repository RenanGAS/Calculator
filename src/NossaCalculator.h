#pragma once

#include "calculator.h"

#include "NossaCpu.h"
#include "NossoDisplay.h"
#include "NossasKeys.h"
#include "NossoKeyboard.h"

class NossaCalculator: public Calculator
{
    Cpu* cpu;
    Keyboard* keyboard;
    public:
    virtual void setDisplay(Display* );
    virtual void setCpu(Cpu* );
    virtual void setKeyboard(Keyboard* );
};