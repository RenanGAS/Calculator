#include "calculatorv2.h"
#include <iostream>
#include <cmath>

//class Display methods
void Display::add(Digit digit)
{
    std::cout << int(digit);
}

void Display::add(Operation op)
{
    switch(op)
    {
        case SUM:
            std::cout << "+";
            break;
        case SUBTRACTION:
            std::cout << "-";
            break;
        case MULTIPLICATION:
            std::cout << "x";
            break;
        case DIVISION:
            std::cout << "/";
            break;
        case SQRT:
            std::cout << "^ (1/2)";
            break;
        case PERCENT:
            std::cout << "%";
            break;
        default:
            std::cout << " ";
            break;
    }
}

void Display::clear()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n";
}

//Class Cpu methods

void Cpu::left_align(int arg)
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
void Cpu::clear_array(Digit *array)
{
    for(int i = 0; i < MAX_DIGITS; i++)
    {
        array[i] = ZERO;
    }
}

int Cpu::convert_to_int(Digit *arg, int count)
{
    int result = 0;
    for(int i = 0; i < count; i++)
    {
        result += arg[i] * pow(10, count - i - 1);
    }
    return result;
}

void Cpu::convert_to_digit(int num, Digit *result)
{
    int helper = num;
    int i = 0;
    while(helper != 0)
    {
        result[i++] = Digit(helper % 10);
        helper /= 10;
    }
    this->count1 = i;
}

void Cpu::call_display()
{
    int zero_checker = 0;

    for(int i = 0; i < this->count1; i++)
    {
        if((arg1[i] != 0) || zero_checker) 
        {
            this->display->add(arg1[i]);
            zero_checker = 1;
        }
    }
    zero_checker = 0;
    this->display->add(this->op);
    if ((this->op != NONE) && (this->op != SQRT))
    {
        for(int i = 0; i < this->count2; i++)
        {
            if((arg2[i] != 0) || zero_checker) 
            {
                this->display->add(arg2[i]);
                zero_checker = 1;
            }
        }
    }
}

void Cpu::Operate()
{
    int operand1 = this->convert_to_int(this->arg1, this->count1);
    int operand2 = this->convert_to_int(this->arg2, this->count2);
    int result;
    //printf("\n\nOperand1: %d", operand1);
    //printf("\nOperand2: %d", operand2);
    //printf("\nOperation: %d", this->op);
    switch (this->op)
    {
        case SUM:
            result = operand1 + operand2;
            //TODO: check if the result is bigger than MAX_DIGITS
            break;
        case SUBTRACTION:
            result = operand1 - operand2;
            break;
        case MULTIPLICATION:
            result = operand1 * operand2;
            //TODO: check if the result is bigger than MAX_DIGITS
            break;
        case DIVISION:
            result = operand1 / operand2;
            //TODO: check if operand2 is 0
            break;
        case SQRT:
            //TODO: check if operand1 is negative
            if (operand1 > 0)
            {
                result = sqrt(operand1);
            }
            else
            {
                //TODO: display error
            }
            break;
        case NONE:
            //TODO: this is a mistake and should be handled
            /* error, this is a bug with your calculator,
            please don't contact your warranty */
            break;
            case PERCENT:
            //DONE: check if it follows a real calculator
            //TODO: it doesn't, fix it
            result = operand1 * 100;
            break;
    }
    //printf("\nResult: %d\n\n", result);
    clear_array(this->arg1);
    convert_to_digit(result, this->arg1);
    left_align(1);
    clear_array(this->arg2);
    this->count2 = 0;
    this->op = NONE;
    //this->display->show(this);
}

void Cpu::setDisplay(Display* display)
{
    this->display = display;
}

void Cpu::receiveDigit(Digit d)
{
    if ((this->count1 < MAX_DIGITS))
    {
        this->arg1[this->count1++] = d;
    }
    else if ((count2 < MAX_DIGITS) && (this->op != NONE))
    {
        this->arg2[this->count2++] = d;
    }
    call_display();
}

void Cpu::receiveOperation(Operation op)
{
    if (this->op == NONE)
    {
        this->op = op;
    }
    else
    {
        this->Operate();
        clear_array(this->arg1);
    }
    call_display();
}

void Cpu::receiveControl(Control c)
{
    switch (c)
    {
        case CLEAR:
            //TODO: implement clear
        case RESET:
            clear_array(this->arg1);
            clear_array(this->arg2);
            this->count1 = 0;
            this->count2 = 0;
            this->op = NONE;
            break;
        case EQUALS:
            this->Operate();
            break;
        case MRC:
            //TODO: implement MRC
            break;
        case MMINUS:
            //TODO: implement MMINUS
            break;
        case MPLUS:
            //TODO: implement MPLUS
            break;
        case OFF:
            //TODO: implement OFF
    }
    call_display();
}
Cpu::Cpu()
{
    this->arg1 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
    this->arg2 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
    this->count1 = 0;
    this->count2 = 0;
    this->op = NONE;
}

Cpu::~Cpu()
{
    free(this->arg1);
    free(this->arg2);
}