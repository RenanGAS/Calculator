#include "calculator.h"
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

int OpButton::getValue()
{
    return this->op;
}

void OpButton::press()
{
    kb->transport(this->op, kb->cp);
}

// class DigitButton

DigitButton::DigitButton(Digit dg)
{
    this->dg = dg;
}

int DigitButton::getValue()
{
    return this->dg;
}

void DigitButton::press()
{
    cout << "\nEnviando :" << dg;
    kb->transport(this->dg, kb->cp);
}

// class ControlButton

ControlButton::ControlButton(Control ctrl)
{
    ControlButton::ctrl = ctrl;
}

int ControlButton::getValue()
{
    return this->ctrl;
}

void ControlButton::press()
{
    kb->transport(this->ctrl, kb->cp);
}

// class Display

Display::Display()
{
    this->disp[0] = '\0';
    strcat(disp, "0");
}

void Display::show()
{
    cout << "\n"
         << this->disp;
    cout << "\n";
}

void Display::clear()
{
    this->disp[0] = '\0';
    strcat(disp, "0");
}

// class Keyboard

Keyboard::Keyboard()
{
    this->countBt = 0;

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

char *Keyboard::sendInput(char *input, Cpu *cp)
{
    cp->receiveInput(input, this);
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

int Cpu::decodeNum(char *input)
{
    if (!strcmp(input, "0"))
    {
        return ZERO;
    }
    else if (!strcmp(input, "1"))
    {
        return ONE;
    }
    else if (!strcmp(input, "2"))
    {
        return TWO;
    }
    else if (!strcmp(input, "3"))
    {
        return THREE;
    }
    else if (!strcmp(input, "4"))
    {
        return FOUR;
    }
    else if (!strcmp(input, "5"))
    {
        return FIVE;
    }
    else if (!strcmp(input, "6"))
    {
        return SIX;
    }
    else if (!strcmp(input, "7"))
    {
        return SEVEN;
    }
    else if (!strcmp(input, "8"))
    {
        return EIGHT;
    }
    else if (!strcmp(input, "9"))
    {
        return NINE;
    }

    return -1;
}

int Cpu::decodeOp(char *input)
{
    if (!strcmp(input, "+"))
    {
        return PLUS;
    }
    else if (!strcmp(input, "-"))
    {
        return MINUS;
    }
    else if (!strcmp(input, "*"))
    {
        return MULT;
    }
    else if (!strcmp(input, "/"))
    {
        return DIV;
    }

    return -1;
}

int Cpu::decodeCtrl(char *input)
{
    if (!strcmp(input, "m+"))
    {
        return M_PLUS;
    }
    else if (!strcmp(input, "m-"))
    {
        return M_MINUS;
    }
    else if (!strcmp(input, "mrc"))
    {
        return MRC;
    }
    else if (!strcmp(input, "ce"))
    {
        return CE;
    }
    else if (!strcmp(input, "="))
    {
        return EQUALS;
    }

    return -1;
}

void Cpu::receiveInput(char *input, Keyboard *kb)
{
    while (strcmp(input, "off") != 0)
    {
        cout << "\n> ";
        cin >> input;

        if (decodeNum(input) != -1)
        {
            cout << "\nTESTES\n";
            cout << "\nEntrada convertida para o inteiro: " << decodeNum(input) << "\n";
            
            int x = kb->bt[decodeNum(input)]->getValue();

            cout << "\nDigito armazenado na posição do inteiro: " << x << "\n";
            cout << "\nFIM\n";

            kb->bt[decodeNum(input)]->press();
        }
        else if (decodeOp(input) != -1)
        {
            kb->bt[decodeOp(input)]->press();
        }
        else if (decodeCtrl(input) != -1)
        {
            kb->bt[decodeCtrl(input)]->press();
        }
        else
        {
            cout << "\nEntrada inválida\n";
        }
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

// class Calculator

void Calculator::setKeyboard(Keyboard *kb)
{
    this->kb = kb;
}
void Calculator::setCpu(Cpu *cp)
{
    this->cp = cp;
}
void Calculator::setDisplay(Display *disp)
{
    this->disp = disp;
}

void Calculator::run()
{
   
}
