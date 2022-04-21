#pragma once

#define MAX_DIGITS 8

enum Digit
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
};
enum Operation
{
	ADDITION,
	SUBTRACTION,
	DIVISION,
	MULTIPLICATION,
	SQUARE_ROOT,
	PERCENTAGE,
	NONE
};
enum Control
{
	CLEAR,
	RESET,
	DECIMAL_SEPARATOR,
	MEMORY_READ_CLEAR,
	MEMORY_ADDITION,
	MEMORY_SUBTRACTION,
	EQUALS
};
enum Signal
{
	POSITIVE,
	NEGATIVE
};

class Display
{
public:
	virtual void add(Digit) = 0;
	virtual void SetDecimalSeparator() = 0;
	virtual void setSignal(Signal) = 0;
	virtual void setError() = 0;
	virtual void clear() = 0;
};

class Receiver
{
public:
	virtual void receiveDigit(Digit) = 0;
	virtual void receiveOperation(Operation) = 0;
	virtual void receiveControl(Control) = 0;
};

class Cpu : public Receiver
{
public:
	virtual void setDisplay(Display *) = 0;
	virtual void receiveDigit(Digit) = 0;
	virtual void receiveOperation(Operation) = 0;
	virtual void receiveControl(Control) = 0;
};

class Key;

class Keyboard : public Receiver
{
public:
	virtual void setCpu(Cpu *) = 0;
	virtual void addKey(Key *) = 0;
	virtual void receiveDigit(Digit) = 0;
	virtual void receiveOperation(Operation) = 0;
	virtual void receiveControl(Control) = 0;
};

class Calculator
{
	Display *display;
	Keyboard *keyboard;
	Cpu *cpu;

public:
	virtual void setDisplay(Display *) = 0;
	virtual void setCpu(Cpu *) = 0;
	virtual void setKeyboard(Keyboard *) = 0;
};

class Key
{
public:
	virtual void setReceiver(Receiver *);
	virtual void press() = 0;
};

class KeyDigit : public Key
{
public:
	virtual void press();
};

class KeyOperation : public Key
{
public:
	virtual void press();
};

class KeyControl : public Key
{
public:
	virtual void press();
};