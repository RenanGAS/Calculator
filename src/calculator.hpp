#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <cstring>
using namespace std;

#define MAX_STACK 17
#define MAX_DISP 10

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
    char disp[MAX_DISP];
    void show();
    void clear();
};

class Keyboards
{
public:
    Buttons *bt[200];
    int countBt;
    Cpus *cp;

    void setButtons(Buttons *bt);
    void setCpu(Cpus *cp);
    void transport(int x, Cpus *cp);
};

class Cpus
{
public:
    int top;
    int stack[MAX_STACK];
    char input[MAX_DISP];
    Displays *disp;

    void setDisplay(Displays *disp);
    void sendDisp();
    void receiveInput(int x, int *stack);
    void processInput(int *stack);
};

class Calculators
{
    Keyboards *kb;
    Cpus *cp;
    Displays *disp;
};

#endif
