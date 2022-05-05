#include "OurKeyboard.h"
#include <iostream>
#include <cmath>

//Class Keyboard methods

//constructs the keyboard
OurKeyboard::OurKeyboard()
{
	this->cpu = NULL;
	this->KeysCount = 0;
}

//Sets the cpu for a keyboard
void OurKeyboard::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
}

//Adds a key to the keyboard and updates the counter
void OurKeyboard::addKey(Key* key)
{
	if(this->KeysCount < 200)
	{
		this->keys[this->KeysCount++] = key;
		key->setReceiver(this);
	}
	else
	{
		std::cout << "Keyboard is full" << std::endl;
	}
}

//Passes digits to the cpu
void OurKeyboard::receiveDigit(Digit d)
{
	this->cpu->receiveDigit(d);
}

//Passes operations to the cpu
void OurKeyboard::receiveOperation(Operation op)
{
	this->cpu->receiveOperation(op);
}

//Passes Control to the cpu
void OurKeyboard::receiveControl(Control c)
{
	this->cpu->receiveControl(c);
}