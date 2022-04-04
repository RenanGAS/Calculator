#include <iostream>

enum Digit: unsigned char
{
    ZERO = 0,
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

enum Operation: unsigned char
{
    PLUS = 10,
    MINUS,
    TIMES,
    DIVIDED,
    SQT,
    PERCENT
};

enum Control: unsigned char
{
    MEMORY = 16,
    MEMORY_PLUS,
    MEMORY_MINUS,
    CLEAR,
    EQUALS,
    OFF
};


class Display
{
public:
    void add(Digit digit) {}
    void add(Operation op) {}
    void add(Control command) {}
    void clear() {}
};

class Key
{
    Keyboard *keyboard;
    // Digit digit;

public:
    // Key(Digit d) : digit(d) {}
    /*void press() {
        this->keyboard->receiveDigit(this->digit);
    } */
    virtual void press() = 0;
    void setKeyboard(Keyboard *keyboard)
    {
        this->keyboard = keyboard;
    }
};

class Control_key: public Key
{
    Control command;
    public:
    Control_key(Control comm) : command(comm) {}

    
};

class Digit_key: public Key
{
    Digit digit;
    public:
    Digit_key(Digit d) : digit(d) {}
};

class Operation_Key: public Key
{
    Operation op;
    public:
    Operation_Key(Operation op) : op(op) {}
};

class Keyboard
{
    Key *keys[200];
    int KeysCount;
    Cpu *cpu;

public:

    Keyboard(Cpu *cpu)
    {
        Keyboard::cpu = cpu;
    }

    void addKey(Key *key)
    {
        this->keys[this->KeysCount++] = key;
        key->setKeyboard(this);
    }

    void receiveDigit(Digit d){}
};

class Cpu
{
    Display *display;

};