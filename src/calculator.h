#pragma once

#include <iostream>
#include <cstring>
using namespace std;

#define MAX_STACK 17
#define MAX_DISP 10

enum Digit
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

enum Operation
{
    PLUS = 10,
    MINUS,
    MULT,
    DIV,
    SQRT,
    PERCENT

};

enum Control
{
    MRC = 16,
    M_PLUS,
    M_MINUS,
    CE,
    EQUALS,
    OFF
};

class Keyboard;

class Button
{
public:
    Keyboard *kb;
    void virtual press() = 0;
    int virtual getValue() = 0;
    void setKeyboard(Keyboard *kb);
};

class OpButton : public Button
{
    Operation op;

public:
    OpButton(Operation op);
    int getValue();
    void press();
};

class DigitButton : public Button
{
    Digit dg;

public:
    DigitButton(Digit dg);
    int getValue();
    void press();
};

class ControlButton : public Button
{
    Control ctrl;

public:
    ControlButton(Control ctrl);
    int getValue();
    void press();
};

class Display
{
public:
    char disp[MAX_DISP];
    Display();
    void show();
    void clear();
};

class Cpu;

class Keyboard
{
public:
    Button *bt[200];
    int countBt;
    Cpu *cp;

    Keyboard();
    void setButtons(Button *bt);
    void setCpu(Cpu *cp);

    char *sendInput(char *input, Cpu *cp);
    void transport(int x, Cpu *cp);
};

class Cpu
{
public:
    int top;
    int stack[MAX_STACK];
    char input[MAX_DISP];
    Display *disp;

    int decodeNum(char *input);
    int decodeOp(char *input);
    int decodeCtrl(char *input);
    void receiveInput(char *input, Keyboard *kb);

    void setDisplay(Display *disp);
    void sendDisp();
    void processInput(int *stack);
};

class Calculator
{
public:
    Keyboard *kb;
    Cpu *cp;
    Display *disp;

    void setKeyboard(Keyboard *kb);
    void setCpu(Cpu *cp);
    void setDisplay(Display *disp);
    void run();
};