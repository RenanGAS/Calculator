#pragma once

#include "calculator.h"

class NossaKey: virtual public Key
{
public:
    virtual void setReceiver(Receiver *);
};

class NossaKeyDigit : public NossaKey, KeyDigit
{
    Digit digit;

public:
    NossaKeyDigit(Digit);
    void press();
};

class NossaKeyOperation : public NossaKey, KeyOperation
{
    Operation operation;

public:
    NossaKeyOperation(Operation);
    void press();
};

class NossaKeyControl : public NossaKey, KeyControl
{
    Control control;

public:
    NossaKeyControl(Control);
    void press();
};