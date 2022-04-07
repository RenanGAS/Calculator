#include "calculator.hpp"
#include <math.h>
#include <sstream>
using namespace std;

// class Button

void Button::setKeyboard(Keyboard *kb)
{
    this->kb = kb;
}

// class OpButton

OpButton::OpButton(Operation op)
{
    OpButton::op = op;
}

void OpButton::press()
{
    kb->transport(OpButton::op, kb->cp);
}

// class DigitButton

DigitButton::DigitButton(Digit dg)
{
    DigitButton::dg = dg;
}

void DigitButton::press()
{
    kb->transport(DigitButton::dg, kb->cp);
}

// class ControlButton

ControlButton::ControlButton(Control ctrl)
{
    ControlButton::ctrl = ctrl;
}

void ControlButton::press()
{
    kb->transport(ControlButton::ctrl, kb->cp);
}

// class Display

void Display::show() {}
void Display::clear() {}

// class Keyboard

Keyboard::Keyboard()
{
    DigitButton d0(ZERO), d1(ONE), d2(TWO), d3(THREE), d4(FOUR), d5(FIVE), d6(SIX), d7(SEVEN), d8(EIGHT), d9(NINE);
    OpButton opPLUS(PLUS), opMINUS(MINUS), opDIV(DIV), opMULT(MULT), opSQRT(SQRT), opPERCENT(PERCENT);
    ControlButton ctMP(M_PLUS), ctMM(M_MINUS), ctMRC(MRC), ctCE(CE), ctEQ(EQUALS), ctOFF(OFF);
    
    setButtons(&d0);
    setButtons(&d1);
    setButtons(&d2);
    setButtons(&d3);
    setButtons(&d4);
    setButtons(&d5);
    setButtons(&d6);
    setButtons(&d7);
    setButtons(&d8);
    setButtons(&d9);

    setButtons(&opPLUS);
    setButtons(&opMINUS);
    setButtons(&opDIV);
    setButtons(&opMULT);
    setButtons(&opSQRT);
    setButtons(&opPERCENT);

     setButtons(&ctMP);
    setButtons(&ctMM);
    setButtons(&ctMRC);
    setButtons(&ctCE);
    setButtons(&ctEQ);
    setButtons(&ctOFF);
}

void Keyboard::setButtons(Button *bt)
{
    this->bt[this->countBt++] = bt;
    bt->setKeyboard(this);
}

void Keyboard::setCpu(Cpu *cp)
{
    this->cp = cp;
}

void Keyboard::transport(int x, Cpu *cp)
{
    cp->receiveInput(x, cp->stack, cp->input);
}

// class Cpu

void Cpu::setDisplay(Display *disp)
{
    this->disp = disp;
}

void Cpu::sendDisp()
{
    strcpy(this->disp->disp, this->input);
}

void Cpu::receiveInput(int x, int *stack, char *input)
{
    for (int i = 0; i < MAX_STACK; i++)
    {
        stack[i] = x;
    }
}

void Cpu::processInput(int *stack)
{
    int n1 = 0, count1 = 0, n2 = 0, count2 = 0, op = 0, res = 0, countR = 0;

    if (count2 < 8 && stack[top] < 10)
    {
        n2 += stack[top] * pow(10, count2);
        count2++;
        top--;
    }
    else if (count1 < 8 && stack[top] < 10)
    {
        n1 += stack[top] * pow(10, count1);
        count1++;
        top--;
    }
    else
    {
        op = top;
    }

    if (top == -1)
    {
        switch (op)
        {
        case 10:
            res = n1 + n2;
            break;
        case 11:
            res = n1 - n2;
            break;
        case 12:
            res = n1 * n2;
            break;
        case 13:
            res = n1 / n2;
            break;
            // case 14:
            //     res = n1 + n2;
            //     break;
            // case 15:
            //     res = n1 + n2;
            //     break;

        default:
            res = -1;
            break;
        }
    }

    stringstream ss;
    ss << res;
    char *s;
    ss >> s;
    strcpy(input, s);
}

Calculator::Calculator()
{
}

void Calculator::setKeyboards(Keyboard *kb)
{
    this->kb = kb;
}
void Calculator::setCpus(Cpu *cp)
{
    this->cp = cp;
}
void Calculator::setDisplays(Display *disp)
{
    this->disp = disp;
}
