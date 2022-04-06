#include "calculator.hpp"
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
    Buttons::kb->transport(OpButtons::op);
}

// class DigitButtons

DigitButtons::DigitButtons(Digits dg)
{
    DigitButtons::dg = dg;
}

void DigitButtons::press()
{
    Buttons::kb->transport(DigitButtons::dg);
}

// class ControlButtons

ControlButtons::ControlButtons(Controls ctrl)
{
    ControlButtons::ctrl = ctrl;
}

void ControlButtons::press()
{
    Buttons::kb->transport(ControlButtons::ctrl);
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

void Keyboards::transport(Element e) {}

// class Cpus

int *Cpus::handleElem(Element *e) {}
int Cpus::calculator(int *s) {}
char *Cpus::toDisplay(int resp) {}