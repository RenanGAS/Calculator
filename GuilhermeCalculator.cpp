#include <iostream>
#include <cmath>

#include "calculator.h"
#include "GuilhermeCalculator.h"
//Class Calculator methods

//Sets the keyboard for a calculator

void GuilhermeCalculator::setKeyboard(Keyboard* keyboard)
{
	this->keyboard = keyboard;
}

//Sets the display for a calculator
void GuilhermeCalculator::setDisplay(Display* display)
{
	display;
}

//Sets the cpu for a calculator
void GuilhermeCalculator::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
}

Display* GuilhermeCalculator::getDisplay()
{
	return this->display;
}

Cpu* GuilhermeCalculator::getCpu()
{
	return this->cpu;
}

Keyboard* GuilhermeCalculator::getKeyboard()
{
	return this->keyboard;
}
