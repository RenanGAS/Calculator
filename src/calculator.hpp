#ifndef CALC_H
#define CALC_H

#include <iostream>
using namespace std;

#define MAX 50

class Element
{
    char type[30];
};

class Digits : public Element
{
public:
    enum
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
};

class Operations : public Element
{
public:
    enum
    {
        PLUS = 10,
        MINUS,
        MULT,
        DIV,
        SQRT,
        PERCENT
    };
};

class Controls : public Element
{
public:
    enum
    {
        MRC = 16,
        M_PLUS,
        M_MINUS,
        CE,
        EQUALS,
        OFF
    };
};

class Buttons
{
public:
    Keyboards *kb;
    void virtual press() = 0;
    void setKeyboard(Keyboards *kb);
};

class OpButtons : public Buttons
{
    Operations op;

public:
    OpButtons(Operations op);
    void press();
};

class DigitButtons : public Buttons
{
    Digits dg;

public:
    DigitButtons(Digits dg);
    void press();
};

class ControlButtons : public Buttons
{
    Controls ctrl;

public:
    ControlButtons(Controls ctrl);
    void press();
};

class Displays
{
public:
    void show();
    void clear();
};

class Keyboards
{
    Buttons *bt[200];
    int countBt;
    Cpus *cp;

public:
    void setButtons(Buttons *bt);
    void setCpu(Cpus *cp);
    void transport(Element e);
};

class Cpus
{
    int top;
    int stack[MAX];
    Displays *disp;

    int *handleElem(Element *e);
    int calculator(int *s);
    char *toDisplay(int resp);
};

class Calculators
{
    Keyboards *kb;
    Cpus *cp;
    Displays *disp;
};

#endif
