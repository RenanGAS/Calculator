#pragma once

#include "calculator.h"

class OurKeyboard : public Keyboard
{
	Cpu *cpu;
	Key *keys[200];
	int KeysCount;

public:
	OurKeyboard();
	void setCpu(Cpu *);
	void addKey(Key *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
};