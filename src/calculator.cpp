#include "calculator.hpp"


void Display::add(Digit digit)
{
    std::cout << int(digit);
}
void Display::add(Operation op) {}
void Display::add(Control command) {}
void Display::show(Cpu *cpu)
{
    Digit *number1 = (cpu->getOperand1());
    int counter1 = cpu->get_count1();
    Digit *number2 = (cpu->getOperand2());
    int counter2 = cpu->get_count2();
    Operation op = cpu->getOperation();
    int zero_checker = 0;
    for(int i = 0; i < counter1; i++)
    {
        if((number1[i] != 0) || zero_checker) 
        {
            std::cout << int(number1[i]);
            zero_checker = 1;
        }
    }
    zero_checker = 0;
    std::cout << " ";
    switch (op)
    {
        case PLUS:
            std::cout << "+";
            break;
        case MINUS:
            std::cout << "-";
            break;
        case TIMES:
            std::cout << "x";
            break;
        case DIVIDED:
            std::cout << "/";
            break;
        case SQTR:
            std::cout << "^ (1/2)";
            break;
        case PERCENT:
            std::cout << "%";
            break;
        default:
            break;

    }
    std::cout << " ";
    for (int i = 0; i < counter1; i++)
    {
        if((number2[i] != 0) || (zero_checker))
        {
            std::cout << int(number2[i]);
        }
    }
    
}
void Display::clear() {}

void Key::setKeyboard(Keyboard *keyboard)
{
    this->keyboard = keyboard;
}

Control_key::Control_key(Control comm)
{
    this->command = comm;
}

void Control_key::press()
{
    this->keyboard->receiveKeyPress(this->command);
}

Digit_key::Digit_key(Digit d)
{
    this->digit = d;
}

void Digit_key::press()
{
    this->keyboard->receiveKeyPress(this->digit);
}

Operation_Key::Operation_Key(Operation op)
{
    this->op = op;
}

void Operation_Key::press()
{
    this->keyboard->receiveKeyPress(this->op);
}

Keyboard::Keyboard(Cpu *cpu)
{
    this->cpu = cpu;
    this->KeysCount = 0;
}

void Keyboard::addKey(Key *key)
{
    this->keys[this->KeysCount++] = key;
    key->setKeyboard(this);
}
void Keyboard::receiveKeyPress(Digit digit)
{
    this->cpu->receiveInput(digit);
}
void Keyboard::receiveKeyPress(Operation op)
{
    this->cpu->receiveInput(op);
}
void Keyboard::receiveKeyPress(Control command)
{
    this->cpu->receiveInput(command);
}
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

Cpu::Cpu(Display *display)
{
    this->display = display;
    this->arg1 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
    this->arg2 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
    this->count1 = 0;
    this->count2 = 0;
    this->op = NONE;
}

void Cpu::receiveInput(Digit d)
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

void Cpu::receiveInput(Operation op)
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

void Cpu::receiveInput(Control command)
{
    //TODO: implement
}

void Cpu::operate()
{
    int operand1 = this->convert_to_int(this->arg1, this->count1);
        int operand2 = this->convert_to_int(this->arg2, this->count2);
        int result;
        //printf("\n\nOperand1: %d", operand1);
        //printf("\nOperand2: %d", operand2);
        //printf("\nOperation: %d", this->op);
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
        //printf("\nResult: %d\n\n", result);
        clear_array(this->arg1);
        convert_to_digit(result, this->arg1);
        left_align(1);
        clear_array(this->arg2);
        this->count2 = 0;
        this->op = NONE;
        //this->display->show(this);
}

Digit *Cpu::getOperand1()
{
    return this->arg1;
}
int Cpu::get_count1()
{
    return this->count1;
}
int Cpu::get_count2()
{
    return this->count2;
}
Digit *Cpu::getOperand2()
{
    return this->arg2;
}
Operation Cpu::getOperation()
{
    return this->op;
}