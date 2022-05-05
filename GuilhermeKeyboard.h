#pragma once

#include "calculator.h"

class GuilhermeKeyboard : public Keyboard
{
	Key *keys[200];
	int KeysCount;

public:
	GuilhermeKeyboard();
	// void setCpu(Cpu *); defined in teacher's .cpp
	void addKey(Key *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
};