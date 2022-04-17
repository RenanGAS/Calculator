#include "calculator.h"
#include <iostream>
#include <cmath>

//Class Keyboard methods

//constructs the keyboard
Keyboard::Keyboard()
{
	this->cpu = NULL;
	this->KeysCount = 0;
}

//Sets the cpu for a keyboard
void Keyboard::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
}

//Adds a key to the keyboard and updates the counter
void Keyboard::addKey(Key* key)
{
	std::cout << "Key count is:" << this->KeysCount << std::endl;
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
void Keyboard::receiveDigit(Digit d)
{
	this->cpu->receiveDigit(d);
}

//Passes operations to the cpu
void Keyboard::receiveOperation(Operation op)
{
	this->cpu->receiveOperation(op);
}

//Passes Control to the cpu
void Keyboard::receiveControl(Control c)
{
	this->cpu->receiveControl(c);
}