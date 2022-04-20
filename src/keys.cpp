#include "keys.h"
#include <iostream>
#include <cmath>

//Class Key methods

//Sets a receiver to the key
void NossaKey::setReceiver(Receiver* receiver)
{
	this->receiver = receiver;
}

//Class KeyDigit methods

//constructs a key digit
NossaKeyDigit::NossaKeyDigit(Digit d)
{
	this->digit = d;
}

//Sends a digit to the receiver
void NossaKeyDigit::press()
{
	this->receiver->receiveDigit(this->digit);
}

//Class KeyOperation methods

//constructs a key operation
NossaKeyOperation::NossaKeyOperation(Operation op)
{
	this->operation = op;
}

//Sends a operation to the receiver
void NossaKeyOperation::press()
{
	this->receiver->receiveOperation(this->operation);
}

//Class KeyControl methods

//constructs a key control
NossaKeyControl::NossaKeyControl(Control c)
{
	this->control = c;
}

//Sends a control to the receiver
void NossaKeyControl::press()
{
	this->receiver->receiveControl(this->control);
}