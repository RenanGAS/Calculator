#ifndef CALC
#define CALC

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
	MEMORY_READ,
	MEMORY_CLEAR,
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
	Cpu *cpu;

	Key *keys[200];
	int KeysCount;

public:
	Keyboard();
	void setCpu(Cpu *);
	void addKey(Key *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
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
protected:
	Receiver *receiver;

public:
	void setReceiver(Receiver *);
	virtual void press() = 0;
};

class KeyDigit : public Key
{
	Digit digit;

public:
	KeyDigit(Digit);
	void press();
};

class KeyOperation : public Key
{
	Operation operation;

public:
	KeyOperation(Operation);
	void press();
};

class KeyControl : public Key
{
	Control control;

public:
	KeyControl(Control);
	void press();
};

#endif