#include "calculator.h"
#include <iostream>
#include <cmath>

//Class Cpu methods

//makes the number "complete" as in ready to operate
void Cpu::left_align(int arg)
{
	int* count;
	Digit** array;
	int* helper;
	if(arg == 2)
	{
		*helper = this->count2; //number of digits in the number
		* array = this->arg2;
		*count = this->count2;
	}
	else
	{
		*helper = this->count1;
		* array = this->arg1;
		*count = this->count1;
	}
	if (*count + 1 > MAX_DIGITS)
	{
		return;
	}
	for(int i = 0; i < *helper; i++) //transfers the numbers to the rightmost side
	{
		*array[MAX_DIGITS - *helper + i] = *array[i];
		*array[i] = ZERO;
	}
	if(arg == 2) this->count2 = MAX_DIGITS;
	else this->count1 = MAX_DIGITS;
}

//clears an array of digits OBS: this method does not clear the count of the array currently
void Cpu::clear_array(Digit *array)
{
	for(int i = 0; i < MAX_DIGITS; i++)
	{
		array[i] = ZERO;
	}
}

//converts a finished array of digits to a number
int Cpu::convert_to_int(Digit *arg, int count)
{
	int result = 0;
	int digit;
	for(int i = 0; i < count; i++)
	{
		switch (arg[i])
		{
		case ZERO:
			digit = 0;
		case ONE:
			digit = 1;
			break;
		case TWO:
			digit = 2;
		case THREE:
			digit = 3;
		case FOUR:
			digit = 4;
		case FIVE:
			digit = 5;
		case SIX:
			digit = 6;
		case SEVEN:
			digit = 7;
		case EIGHT:
			digit = 8;
		case NINE:
			digit = 9;
		default:
			break;
		}
		result += digit * pow(10, count - i - 1);
	}
	return result;
}

//converts a number to an array of digits and returns the 1 if the number is too big
int Cpu::convert_to_digit(int num, Digit *result, int& count)
{
	int helper = num;
	int i = 0;
	while(helper != 0)
	{
		if(i == MAX_DIGITS) 
		{
			return 1;
			//HANDLING ERRORS
		}
		result[i++] = Digit(helper % 10);
		helper /= 10;
	}
	count = i;
	return 0;
}

//contains all the logic to call the display methods
void Cpu::call_display()
{
	//TODO: change everything
	/* if(this->display == NULL) return;
	int zero_checker = 0;
	for(int i = 0; i < this->count1; i++)
	{
		if((arg1[i] != 0) || zero_checker) 
		{
			this->display->add(arg1[i]);
			zero_checker = 1;
		}
	}

	if ((this->op != NONE) && (this->op != SQUARE_ROOT))
	{
		for(int i = 0; i < this->count2; i++)
		{
			if((arg2[i] != 0) || zero_checker) 
			{
				this->display->add(arg2[i]);
				zero_checker = 1;
			}
		}
	} */
}

//handles errors and displays them
void Cpu::error_handle()
{   //TODO: check how elgin does it
	clear_array(this->arg1);
	clear_array(this->arg2);
	//TODO: check if the error should be displayed at this moment or later
	if (this->display != NULL) this->display->setError();
	
}

//takes the numbers and the operation and performs the operation
void Cpu::Operate()
{
	int operand1 = this->convert_to_int(this->arg1, this->count1);
	int operand2 = this->convert_to_int(this->arg2, this->count2);
	int result = 0; //inicializing to
	//printf("\n\nOperand1: %d", operand1);
	//printf("\nOperand2: %d", operand2);
	//printf("\nOperation: %d", this->op);
	switch (this->op)
	{
		case ADDITION:
			result = operand1 + operand2;
			//DONE: check if the result is bigger than MAX_DIGITS
			break;
		case SUBTRACTION:
			result = operand1 - operand2;
			break;
		case MULTIPLICATION:
			result = operand1 * operand2;
			//DONE: check if the result is bigger than MAX_DIGITS
			break;
		case DIVISION:
			if(operand2 == 0) this->error_handle();
			else result = operand1 / operand2;
			//DONE: check if operand2 is 0
			break;
		case SQUARE_ROOT:
			//DONE: check if operand1 is negative
			if (operand1 > 0)
			{
				result = sqrt(operand1);
			}
			else
			{
				this->error_handle();
			}
			break;
			case PERCENTAGE:
			//DONE: check if it follows a real calculator
			//TODO: it doesn't, fix it
			result = operand1 * 100;
			break;
	}
	//printf("\nResult: %d\n\n", result);
	clear_array(this->arg1);
	if(convert_to_digit(result, this->arg1, this->count1))
	{
		this->error_handle();
	}
	left_align(1);
	clear_array(this->arg2);
	this->count2 = 0;
	//this->display->show(this);
}

//constructs the cpu
Cpu::Cpu()
{
	this->arg1 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
	this->arg2 = static_cast <Digit*> (calloc(MAX_DIGITS, sizeof(Digit)));
	this->count1 = 0;
	this->count2 = 0;
	this->display = NULL;
}

//destructs the cpu and frees the dinamically allocated arrays
Cpu::~Cpu()
{
	free(this->arg1);
	free(this->arg2);
}

//connects a display to the cpu
void Cpu::setDisplay(Display* display)
{
	this->display = display;
}

//contains the logic to receive the digits and put them in the correct array
void Cpu::receiveDigit(Digit d)
{
	if ((this->count1 < MAX_DIGITS))
	{
		this->arg1[this->count1++] = d;
	}
	else if ((count2 < MAX_DIGITS))
	{
		this->arg2[this->count2++] = d;
	}
	call_display();
}

//contains the logic to receive the operations and operate if needed
void Cpu::receiveOperation(Operation op)
{
	this->op = op;
	//TODO: check if change is needed to accomodate floats
	if (this->count1 != MAX_DIGITS)
	{
		left_align(1);
	}
	else
	{
		this->Operate();
	}
	call_display();
}

//receive the control digit and treat appropriately
void Cpu::receiveControl(Control c)
{
	switch (c)
	{
		case CLEAR:
			//TODO: implement clear
			break;
		case RESET:
			clear_array(this->arg1);
			clear_array(this->arg2);
			this->count1 = 0;
			this->count2 = 0;
			//TODO: make the changes needed to acommodate floats
			break;
		case MEMORY_CLEAR:
			//TODO: implement MRC
			break;
		case MEMORY_SUBTRACTION:
			//TODO: implement MMINUS
			break;
		case MEMORY_ADDITION:
			//TODO: implement MPLUS
			break;
		case MEMORY_READ:
			//TODO: implement MEMREAD
			break;
	}
	call_display();
}