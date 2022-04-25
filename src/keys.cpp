#include <iostream>
#include "calculator.h"
#include <cmath>

//Class Key methods

//Sets a receiver to the key
void Key::setReceiver(Receiver* receiver)
{
	this->receiver = receiver;
}

//Class KeyDigit methods

//constructs a key digit
KeyDigit::KeyDigit(Digit d)
{
	this->digit = d;
}

//Sends a digit to the receiver
void KeyDigit::press()
{
	this->Key::receiver->receiveDigit(this->digit);
}

//Class KeyOperation methods

//constructs a key operation

KeyOperation::KeyOperation(Operation op)
{
	this->operation = op;
}

//Sends a operation to the receiver
void KeyOperation::press()
{
	this->Key::receiver->receiveOperation(this->operation);
}

//Class KeyControl methods

//constructs a key control
KeyControl::KeyControl(Control c)
{
	this->control = c;
}

//Sends a control to the receiver
void KeyControl::press()
{
	this->Key::receiver->receiveControl(this->control);
}