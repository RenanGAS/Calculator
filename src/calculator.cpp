#include "calculator.hpp"
#include <math.h>
#include <sstream>
using namespace std;

// class Buttons

void Buttons::setKeyboard(Keyboards *kb)
{
    this->kb = kb;
}

// class OpButtons

OpButtons::OpButtons(Operations op)
{
    OpButtons::op = op;
}

void OpButtons::press()
{
    kb->transport(OpButtons::op, kb->cp);
}

// class DigitButtons

DigitButtons::DigitButtons(Digits dg)
{
    DigitButtons::dg = dg;
}

void DigitButtons::press()
{
    kb->transport(DigitButtons::dg, kb->cp);
}

// class ControlButtons

ControlButtons::ControlButtons(Controls ctrl)
{
    ControlButtons::ctrl = ctrl;
}

void ControlButtons::press()
{
    kb->transport(ControlButtons::ctrl, kb->cp);
}

// class Displays

void Displays::show() {}
void Displays::clear() {}

// class Keyboards

void Keyboards::setButtons(Buttons *bt)
{
    this->bt[this->countBt++] = bt;
    bt->setKeyboard(this);
}

void Keyboards::setCpu(Cpus *cp)
{
    this->cp = cp;
}

void Keyboards::transport(int x, Cpus *cp)
{
    cp->receiveInput(x, cp->stack);
}

// class Cpus

void Cpus::setDisplay(Displays *disp)
{
    this->disp = disp;
}

void Cpus::sendDisp()
{
    strcpy(this->disp->disp, this->input);
}

void Cpus::receiveInput(int x, int *stack)
{
    for (int i = 0; i < MAX_STACK; i++)
    {
        stack[i] = x;
    }
}

void Cpus::processInput(int *stack)
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
