#include "GuilhermeKeyboard.h"
#include <iostream>
#include <cmath>

//Class Keyboard methods

//constructs the keyboard
GuilhermeKeyboard::GuilhermeKeyboard()
{
	this->cpu = NULL;
	this->KeysCount = 0;
}
/*
//Sets the cpu for a keyboard
void GuilhermeKeyboard::setCpu(Cpu* cpu)
{
	this->cpu = cpu;
} */

//Adds a key to the keyboard and updates the counter
bool GuilhermeKeyboard::addKey(Key* key)
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
	return 0;
}

//Passes digits to the cpu
void GuilhermeKeyboard::receiveDigit(Digit d)
{
	this->cpu->receiveDigit(d);
}

//Passes operations to the cpu
void GuilhermeKeyboard::receiveOperation(Operation op)
{
	this->cpu->receiveOperation(op);
}

//Passes Control to the cpu
void GuilhermeKeyboard::receiveControl(Control c)
{
	this->cpu->receiveControl(c);
}

bool GuilhermeKeyboard::removeKey(Key*)
{
	int checker = 0;
	for(int i = 0; i < this->KeysCount - 1; i++)
	{
		if (this->keys[i])
		{
			checker = 1;
		}
		if(checker)
		{
			this->keys[i] = this->keys[i + 1];
		}
		
	}
	return 0;
}

KeyDigit* GuilhermeKeyboard::queryKeyDigit(Digit) {return NULL;}