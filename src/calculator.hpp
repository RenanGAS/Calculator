#ifndef CALC_H
#define CALC_H

#include <iostream>

enum Digits
{
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

enum Operations
{
    PLUS = 10,
    MINUS,
    MULT,
    DIV,
    SQRT,
    PERCENT
};

enum Controls
{
    MRC = 16,
    M_PLUS,
    M_MINUS,
    CE,
    EQUALS,
    OFF
};

class Buttons
{
    Keyboards *kb;

public:
    void virtual press() = 0;
    void setKeyboard(Keyboards *kb)
    {
        this->kb = kb;
    }
};

class OpButtons : public Buttons
{
    Operations op;

public:
    void setOperation(Operations op)
    {
        OpButtons::op = op;
    }
};

class DigitButtons : public Buttons
{
    Digits dg;

public:
    void setDigit(Digits dg)
    {
        DigitButtons::dg = dg;
    }
};

class ControlButtons : public Buttons
{
    Controls ctrl;

public:
    void setControl(Controls ctrl)
    {
        ControlButtons::ctrl = ctrl;
    }
};

class Displays
{
public:
    void add(Digits *dg)
    {
    }
    
    void add(Controls *ctrl);
    void add(Operations *op);

    void clear();
};

class Keyboards
{
    Buttons *bt[200];
    int countBt;
    Cpus *cp;

public:
    void setButtons(Buttons *bt)
    {
        this->bt[this->countBt++] = bt;
        bt->setKeyboard(this);
    }

    void setCpu(Cpus *cp)
    {
        this->cp = cp;
    }

    void receiveDigit(Digits *dg);
};

class Cpus
{
    Displays *disp;
};

class Calculators
{
    Keyboards *kb;
    Cpus *cp;
    Displays *disp;
};

#endif
