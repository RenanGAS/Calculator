#include "calculator.h"
#include <iostream>
#include <cmath>

//Class Calculator methods

//Sets the keyboard for a calculator
void Calculator::setKeyboard(Keyboard* keyboard)
{
	this->keyboard = keyboard;
}

//Sets the display for a calculator
void Calculator::setDisplay(Display* display)
{
	this->display = display;
}

//Sets the cpu for a calculator
void Calculator::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
}