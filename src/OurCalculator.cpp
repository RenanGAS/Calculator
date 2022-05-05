#include <iostream>
#include <cmath>

#include "calculator.h"
#include "OurCalculator.h"
//Class Calculator methods

//Sets the keyboard for a calculator

void OurCalculator::setKeyboard(Keyboard* keyboard)
{
	this->keyboard = keyboard;
}

//Sets the display for a calculator
void OurCalculator::setDisplay(Display* display)
{
	display;
}

//Sets the cpu for a calculator
void OurCalculator::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
}