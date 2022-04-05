#ifndef CALC_H
#define CALC_H

#include <iostream>
#define MAX 50

enum Digits
{
    ZERO,
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

class Operations
{
    char *name;
};

class Plus : public Operations
{
    int num0;
    int num1;
};

class Buttons
{
    char *name;
    Keyboards *keyboard;
};

class OpButtons : public Buttons
{
    Operations *op;
};

class DigitButtons : public Buttons
{
    Digits *digit;
};

class Displays
{
};

class Keyboards
{
    Buttons *bt;
    Cpus *cp;
};

class Cpus
{
    int top;
    int stack[MAX];
    Displays *disp;
};

class Calculators
{
    Keyboards *kb;
    Cpus *cp;
    Displays *disp;
};

#endif
