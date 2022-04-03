#include <iostream>

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

class Display
{
public:
    void add(Digit digit) {}
    void clear() {}
};

class Key
{
    Keyboard *keyboard;
    Digit digit;

public:
    Key(Digit d) : digit(d) {}
    void press() {
        this->keyboard->receiveDigit(this->digit);
    }
    void setKeyboard(Keyboard *keyboard)
    {
        this->keyboard = keyboard;
    }
};

class Keyboard
{
    Key *keys[200];
    int KeysCount;
    Cpu *cpu;

public:
    void addKey(Key *key)
    {
        this->keys[this->KeysCount++] = key;
        key->setKeyboard(this);
    }

    void receiveDigit(Digit d){}
};

class Cpu
{

};
