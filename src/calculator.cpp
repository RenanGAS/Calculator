#include <iostream>
#include <cmath>

#include "calculator.h"
#include "NossaCalculator.h"
//Class Calculator methods

//Sets the keyboard for a calculator

void NossaCalculator::setKeyboard(Keyboard* keyboard)
{
	this->keyboard = keyboard;
}

//Sets the display for a calculator
void NossaCalculator::setDisplay(Display* display)
{
	 display;
}

//Sets the cpu for a calculator
void NossaCalculator::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
}