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
    void add(Digit digit) 
    {
        std::cout << int(digit);
    }
    void add(Operation op) {}
    void add(Control command) {}
    void show(Cpu *cpu)
    {
        Digit number1 = cpu->getOperand1();
        Digit number2 = cpu->getOperand2();
        Operation op = cpu->getOperation();
    }
    void clear() {}
};

class Key
{
protected:
    Keyboard *keyboard;
    // Digit digit;

public:
    // Key(Digit d) : digit(d) {}
    /*void press() {
        this->keyboard->receivereceiveDigit(this->digit);
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
    void press()
    {
        this->keyboard->receiveKeyPress(this->command);
    }

    
};

class Digit_key: public Key
{
    Digit digit;
    public:
    Digit_key(Digit d) : digit(d) {}
    void press()
    {
        this->keyboard->receiveKeyPress(this->digit);
    }
};

class Operation_Key: public Key
{
    Operation op;
    public:
    Operation_Key(Operation op) : op(op) {}
    void press()
    {
        this->keyboard->receiveKeyPress(this->op);
    }
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
    void receiveKeyPress(Digit d) {}
    void receiveKeyPress(Operation op){}
    void receiveKeyPress(Control command){}
};

class Cpu
{
    Display *display;
    Digit arg1[8];
    int count1 = 0;
    Operation op;
    Digit arg2[8];
    int count2 = 0;
    public:
    Cpu(Display *display) : display(display) {}
    void receiveInput(Digit d)
    {
        if ((count1 < 8) && !(op))
        {
            arg1[count1++] = d;
        }
        else if ((count2 < 8) && (op))
        {
            arg2[count2++] = d;
        }
        this->display->show(this);

    }
    void receiveInput(Operation op)
    {

    }
    void receiveInput(Control command) {}
    Digit getOperand1()
    {
        
    }  
    Digit getOperand2()
    {
        
    }
    Operation getOperation()
    {
        
    }
};