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
    void add(Digit digit) 
    {
        std::cout << int(digit);
    }
    void add(Operation op) {}
    void add(Control command) {}
    void show(Cpu *cpu)
    {
        Digit *number1 = (cpu->getOperand1());
        Digit *number2 = (cpu->getOperand2());
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
        this->cpu = cpu;
        this->KeysCount = 0;
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
    Digit *arg1;
    int count1 = 0;
    Operation op;
    Digit *arg2;
    int count2 = 0;

    void left_align(int arg)
    {
        int helper; //number of digits in the number
        if(arg == 2)
        {
            helper = this->count2; 
            for(int i = 0; i < helper; i++) //transfers the numbers to the rightmost side
            {
                arg2[MAX_DIGITS - helper + i] = arg2[i];
                arg2[i] = ZERO;
            }
            this->count2 = MAX_DIGITS;
        }
        else
        {
            helper = this->count1;
            for(int i = 0; i < helper; i++) //transfers the numbers to the rightmost side
            {
                arg1[MAX_DIGITS - helper + i] = arg1[i];
                arg1[i] = ZERO;
            }
            this->count1 = MAX_DIGITS;
        }

    }


    void clear_array(Digit *array)
    {
        for(int i = 0; i < MAX_DIGITS; i++)
        {
            array[i] = ZERO;
        }
    }


    int convert_to_int(Digit *arg, int count)
    {
        int result = 0;
        for(int i = 0; i < this->count1; i++)
        {
            result += arg[i] * pow(10, count - i - 1);
        }
        return result;
    }


    void convert_to_digit(int arg, Digit *result)
    {
        int helper = arg;
        int i = 0;
        while(helper != 0)
        {
            result[i++] = Digit(helper % 10);
            helper /= 10;
        }
        this->count1 = i;
    }


    public:
    Cpu(Display *display)
    {
        this->display = display;
        this->arg1 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
        this->arg2 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
        this->count1 = 0;
        this->count2 = 0;
        this->op = NONE;
    }
    void receiveInput(Digit d)
    {
        if ((count1 < MAX_DIGITS))
        {
            arg1[count1++] = d;
        }
        else if ((count2 < MAX_DIGITS) && (this->op != NONE))
        {
            arg2[count2++] = d;
        }
        this->display->show(this);


    }
    void receiveInput(Operation op)
    {
        if(this->op != NONE)
        {
            if(this->count2 != 0)
            {
                left_align(2);
                this->operate();
            }
            
        }
        else
        {
            left_align(1);
        }
        this->op = op;

        this->display->show(this);
    }
    void receiveInput(Control command)
    {
    
    }
    void operate()
    {
        int operand1 = this->convert_to_int(this->arg1, this->count1);
        int operand2 = this->convert_to_int(this->arg2, this->count2);
        int result;
        switch (this->op)
        {
            case PLUS:
                result = operand1 + operand2;
                //TODO: check if the result is bigger than MAX_DIGITS
                break;
            case MINUS:
                result = operand1 - operand2;
                break;
            case TIMES:
                result = operand1 * operand2;
                //TODO: check if the result is bigger than MAX_DIGITS
                break;
                case DIVIDED:
                result = operand1 / operand2;
                //TODO: check if operand2 is 0
                break;
                case SQTR:
                //TODO: check if operand1 is negative
                result = sqrt(operand1);
                break;
                case NONE:
                //TODO: this is a mistake and should be handled
                break;
                case PERCENT:
                //TODO: check if it follows a real calculator
                result = operand1 * 100;
                break;
        }
        convert_to_digit(result, this->arg1);
        clear_array(this->arg2);
        this->count2 = 0;
        this->op = NONE;
        this->display->show(this);
    }
    Digit *getOperand1()
    {
        return this->arg1;
    }
    Digit *getOperand2()
    {
        return this->arg2;
    }
    Operation getOperation()
    {
        return this->op;
    }
};