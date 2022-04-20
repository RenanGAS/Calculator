#pragma once

#include "calculator.h"

class NossaKey : public Key
{
protected:
    Receiver *receiver;

public:
    void setReceiver(Receiver *);
    virtual void press() = 0;
};

class NossaKeyDigit : public KeyDigit, NossaKey
{
    Digit digit;

public:
    NossaKeyDigit(Digit);
    void press();
};

class NossaKeyOperation : public KeyOperation, NossaKey
{
    Operation operation;

public:
    NossaKeyOperation(Operation);
    void press();
};

class NossaKeyControl : public KeyControl, NossaKey
{
    Control control;

public:
    NossaKeyControl(Control);
    void press();
};