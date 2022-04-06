#ifndef CALCULATOR.H
#define CALCULATOR.H

#include <iostream>
#include <cmath>
#define MAX_DIGITS 8


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
    SQTR,
    PERCENT,
    NONE
};

enum Control: unsigned char
{
    MEMORY = 17,
    MEMORY_PLUS,
    MEMORY_MINUS,
    CLEAR,
    EQUALS,
    OFF
};



class Display
{
public:
    void add(Digit digit);
    void add(Operation op);
    void add(Control command);
    void show(Cpu *cpu);
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
    void setKeyboard(Keyboard *keyboard);
};

class Control_key: public Key
{
    Control command;
    public:
    Control_key(Control comm);
    void press();

    
};

class Digit_key: public Key
{
    Digit digit;
    public:
    Digit_key(Digit d);
    void press();
};

class Operation_Key: public Key
{
    Operation op;
    public:
    Operation_Key(Operation op);
    void press();
};

class Keyboard
{
    Key *keys[200];
    int KeysCount;
    Cpu *cpu;

public:

    Keyboard(Cpu *cpu);

    void addKey(Key *key);
    void receiveKeyPress(Digit d);
    void receiveKeyPress(Operation op);
    void receiveKeyPress(Control command);
};

class Cpu
{
    Display *display;
    Digit *arg1;
    int count1;
    Operation op;
    Digit *arg2;
    int count2;

    void left_align(int arg);
    void clear_array(Digit *array);


    int convert_to_int(Digit *arg, int count);


    void convert_to_digit(int arg, Digit *result);


    public:
    Cpu(Display *display);
    void receiveInput(Digit d);
    void receiveInput(Operation op);
    void receiveInput(Control command);
    void operate();
    Digit *getOperand1();
    Digit *getOperand2();
    Operation getOperation();
};
#endif