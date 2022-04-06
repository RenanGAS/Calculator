#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <cstring>
using namespace std;

#define MAX 50

class Element
{
public:
    char type[30];
};

class Digits : public Element
{
public:
    Digits(char *type)
    {
        strcpy(type, Digits::type);
    }

    const char ZERO = '0',
               ONE = '1',
               TWO = '2',
               THREE = '3',
               FOUR = '4',
               FIVE = '5',
               SIX = '6',
               SEVEN = '7',
               EIGHT = '8',
               NINE = '9';
};

class Operations : public Element
{
public:
    Operations(char *type)
    {
        strcpy(type, Operations::type);
    }
    const char PLUS = '+',
               MINUS = '-',
               MULT = '*',
               DIV = '/',
               PERCENT = '%';
    //   SQRT = '',
};

class Controls : public Element
{
public:
    Controls(char *type)
    {
        strcpy(type, Controls::type);
    }
    const char MRC[10] = "mrc",
               M_PLUS[10] = "m+",
               M_MINUS[10] = "m-",
               CE[10] = "ce",
               EQUALS[10] = "=",
               OFF[10] = "off";
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
    Operations::Element op;

public:
    OpButtons(Operations op);
    void press();
};

class DigitButtons : public Buttons
{
    Digits::Element dg;

public:
    DigitButtons(Digits dg);
    void press();
};

class ControlButtons : public Buttons
{
    Controls::Element ctrl;

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
