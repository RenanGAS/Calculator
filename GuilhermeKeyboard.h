#pragma once

#include "calculator.h"

class GuilhermeKeyboard : public Keyboard
{
	Cpu *cpu;
	Key *keys[200];
	int KeysCount;

public:
	GuilhermeKeyboard();
	void setCpu(Cpu *);
	void addKey(Key *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
};