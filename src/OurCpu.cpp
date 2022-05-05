#include "OurCpu.h"
#include <iostream>
#include <cmath>

#define MAX_DIGITS 8

// Class Cpu methods

// makes the number "complete" as in ready to operate
void OurCpu::right_align(int arg)
{
	int helper;			//this is used to count without changing the count
	int *count;			//this is used to change the count
	Digit **array;		//this is used to change the array
	int *decimal_point; //this is used to change the decimal point
	if (arg == 2)
	{
		helper = this->count2;
		count = &this->count2;
		array = &this->arg2;
		decimal_point = &this->count_point2;
	}
	else
	{
		helper = this->count1;
		count = &this->count1;
		array = &this->arg1;
		decimal_point = &this->count_point1;
	}
	//this resolves an edge case where this->count = MAX_DIGITS and greater, because no operation is needed
	if (helper + 1 > MAX_DIGITS)
		return;

	if (*decimal_point < MAX_DIGITS)
		(*decimal_point) = MAX_DIGITS - helper + *decimal_point; //this fixes the decimal point
	for (int i = (helper - 1); i >= 0; i--)					   // transfers the numbers to the rightmost side
	{														   //this for transfers from right to left in order to not overrwite any number
		(*array)[MAX_DIGITS - helper + i] = (*array)[i];
		(*array)[i] = ZERO;
	}
	*count = MAX_DIGITS;
}

//clears an array of digits
void OurCpu::clear_array(Digit *array, int *count, int *decimal_count)
{
	for (int i = 0; i < MAX_DIGITS; i++)
	{
		array[i] = ZERO;
	}

	*count = 0;
	*decimal_count = MAX_DIGITS;
	if (array == this->arg1) //as the arg1 can have a negative signal, it must be cleaned when cleaning it
	{
		this->signal = POSITIVE;
	}
}
//transforms a single digit in a single int
int OurCpu::digit_to_int(Digit digit)
{
	switch (digit)
	{
	case ZERO:
		return 0;
	case ONE:
		return 1;
	case TWO:
		return 2;
	case THRE:
		return 3;
	case FOUR:
		return 4;
	case FIVE:
		return 5;
	case SIX:
		return 6;
	case SEVEN:
		return 7;
	case EIGHT:
		return 8;
	case NINE:
		return 9;
	default:
		return 0;
	}
}

Digit OurCpu::int_to_digit(int number)
{
	switch (number)
	{
	case 0:
		return ZERO;
	case 1:
		return ONE;
	case 2:
		return TWO;
	case 3:
		return THRE;
	case 4:
		return FOUR;
	case 5:
		return FIVE;
	case 6:
		return SIX;
	case 7:
		return SEVEN;
	case 8:
		return EIGHT;
	case 9:
		return NINE;
	default:
		return ZERO;
	}
}

//Convert a finished array of digits to an double to accomodate floating points
double OurCpu::convert_to_operands(Digit *arg, int count, int point_count)
{
	double result = 0;
	int digit;
	for (int i = 0; i < count; i++)
	{
		digit = digit_to_int(arg[i]);
		result += digit * pow(10, point_count - i - 1);
	}
	return result;
}

//converts a number to a finished array of digits
int OurCpu::convert_to_digit(double result, Digit *vet, int *count, int *decimal_count)
{
	Digit digit;
	int i = 0;
	int zero_checker = 0;
	*count = 0;
	*decimal_count = 0;
	if(this->arg1 == vet)
	{
		if (result < 0)
		{
			result = -result;
			if (vet == this->arg1)
			{
				this->signal = NEGATIVE;
			}
		}
		else this->signal = POSITIVE;
	}
	double result_helper = result;
	*decimal_count = log10(result_helper) + 1;
	if (*decimal_count > MAX_DIGITS)
	{
		return 1;
	}

	while (*count < *decimal_count)
	{
		if (*count == MAX_DIGITS)
		{
			break;
		}
		digit = int_to_digit(trunc(result / pow(10, MAX_DIGITS - i)));
		if (digit != ZERO)
		{
			zero_checker = 1;
		}
		if (zero_checker)
		{
			vet[*count] = digit;
			*count += 1;
		}
		result = fmod(result, pow(10, MAX_DIGITS - i));
		i++;
	}
	(*count) += (*decimal_count);
	float digito_em_float; 
	for(i = (*decimal_count); i < MAX_DIGITS; i++)
	{
		digito_em_float = result / pow(10, (*decimal_count) -i - 1);
		digito_em_float =  fmod(digito_em_float, 10);
		digit = int_to_digit(digito_em_float);
		vet[i] = digit;
	}
	
	for(i = 0; i < MAX_DIGITS; i++)
	{
		if (vet[i] != ZERO) (*count) = i;
	}
	*count += 1;
	return 0;
}

// contains all the logic to call the display methods
void OurCpu::call_display()
{

	if (this->display == NULL) return;
	this->display->setSignal(this->signal);
	int zero_checker = 0;
	int helper;
	if((this->count_point1 == 0) && (this->op == NONE)) this->display->add(ZERO);
	if(this->count_point1 > this->count1) helper = this->count1;
	else helper = this->count_point1;
	for (int i = 0; i < helper; i++)
	{
		if (((arg1[i] != 0) || zero_checker) && ((this->op == NONE) || (!this->count2) && (this->count_point2)))
		{
			this->display->add(this->arg1[i]);
			zero_checker = 1;
		}
	}
	zero_checker = 0;
	if (this->count1 > this->count_point1)
	{
		if(this->op == NONE || (!this->count2) && (this->count_point2))
		{
			std::cout << ".";
			for(int i = this->count_point1; i < this->count1; i++)
			{
				this->display->add(this->arg1[i]);
			}
		}
	}
	
	zero_checker = 0;

	if(this->count_point2 == 0 && this->op != NONE)
	{
		this->display->add(ZERO);
	}
	if(this->count_point2 > this->count2) helper = this->count2;
	else helper = this->count_point2;
	for (int i = 0; i < helper; i++)
	{
		if (((arg2[i] != 0) || zero_checker))
		{
			this->display->add(this->arg2[i]);
			zero_checker = 1;
		}
	}
	zero_checker = 0;
	if (this->count2 > this->count_point2)
	{
		std::cout << ".";
		for(int i = this->count_point2; i < this->count2; i++)
		{
			this->display->add(this->arg2[i]);
		}
	}
	this->display->clear();
}

// handles errors and displays them
void OurCpu::error_handle()
{
	clear_array(this->arg1, &this->count1, &this->count_point1);
	clear_array(this->arg2, &this->count2, &this->count_point2);
	if (this->display != NULL)
		this->display->setError();
}

void OurCpu::setOperands(int count1, int count2)
{
	if (count1 != MAX_DIGITS)
	{
		right_align(1);
	}

	if (count2 > 0)
	{
		right_align(2);
	}
}

// takes the numbers and the operation and performs the operation
void OurCpu::Operate()
{
	double operand1, operand2;
	operand1 = convert_to_operands(this->arg1, this->count1, this->count_point1);
	operand2 = convert_to_operands(this->arg2, this->count2, this->count_point2);

	double result = 0;
	switch (this->op)
	{
	case ADDITION:
		result = operand1 + operand2;
		break;
	case SUBTRACTION:
		result = operand1 - operand2;
		break;
	case MULTIPLICATION:
		result = operand1 * operand2;
		break;
	case DIVISION:
		if (operand2 == 0)
			this->error_handle();
		else
			result = operand1 / operand2;
		break;
	case SQUARE_ROOT:
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
		if (this->saveOp == ADDITION)
		{
			result = operand1 + (operand1 * (operand2 / 100));
		}
		if (this->saveOp == SUBTRACTION)
		{
			result = operand1 - (operand1 * (operand2 / 100));
		}
		if (this->saveOp == MULTIPLICATION)
		{
			result = operand1 * (operand1 * (operand2 / 100));
		}
		if (this->saveOp == DIVISION)
		{
			result = operand1 / (operand1 * (operand2 / 100));
		}
		break;
	}

	clear_array(this->arg1, &this->count1, &this->count_point1);
	if (this->convert_to_digit(result, this->arg1, &this->count1, &this->count_point1))
	{

		this->error_handle();
	}
	this->right_align(1);

	clear_array(this->arg2, &this->count2, &this->count_point2);
}

// constructs the cpu
OurCpu::OurCpu()
{
	this->arg1 = static_cast <Digit *> (calloc(MAX_DIGITS, sizeof(Digit)));
	this->arg2 = static_cast <Digit *> (calloc(MAX_DIGITS, sizeof(Digit)));
	this->op = NONE;
	this->count1 = 0;
	this->count2 = 0;
	this->count_point1 = MAX_DIGITS;
	this->count_point2 = MAX_DIGITS;
	this->display = NULL;
	this->memory = 0;
	this->mrcFlag = 0;
	this->signal = POSITIVE;
	this->saveOp = NONE;
}

// destructs the cpu and frees the dinamically allocated arrays
OurCpu::~OurCpu()
{
	free(this->arg1);
	free(this->arg2);
}

// connects a display to the cpu
void OurCpu::setDisplay(Display *display)
{
	this->display = display;
	this->display->add(ZERO);
	this->display->clear();
}

// contains the logic to receive the digits and put them in the correct array
void OurCpu::receiveDigit(Digit d)
{
	if ((this->count1 < MAX_DIGITS))
	{
		this->arg1[this->count1++] = d;
	}
	else if ((count2 < MAX_DIGITS && this->op != NONE))
	{
		this->arg2[this->count2++] = d;
	}

	call_display();
}

// contains the logic to receive the operations and operate if needed
void OurCpu::receiveOperation(Operation op)
{
	
	if (op != PERCENTAGE)
	{
		this->saveOp = op;
	}
	
	
	right_align(1);
	if (this->count2 > 0)
	{
		right_align(2);
	}
	if (this->op != NONE)
	{
		this->Operate();
	}
	this->op = op;
	// If the user press the SUBTRACTION Key just after ON/CE, the operand 1 will be negative
	if (this->op == ADDITION && this->count1 == 0)
	{
		this->signal = Signal(NEGATIVE);
	}

	if (this->op == PERCENTAGE)
	{
		receiveControl(EQUAL);
	}
	else
	{
		setOperands(this->count1, this->count2);
		call_display();
	}
}

// receive the control digit and treat appropriately
void OurCpu::receiveControl(Control c)
{
	switch (c)
	{
	case EQUAL:
		setOperands(this->count1, this->count2);
		Operate();
		break;
	case CLEAR:
		this->display->clear();
		break;
	case RESET:
		clear_array(this->arg1, &this->count1, &this->count_point1);
		clear_array(this->arg2, &this->count2, &this->count_point2);
		this->count1 = 0;
		this->count2 = 0;
		this->display->clear();
		break;
	case MEMORY_READ_CLEAR:
		setOperands(this->count1, this->count2);

		if (this->mrcFlag)
		{
			this->mrcFlag = 0;
			break;
		}

		if (this->op == NONE)
		{
			clear_array(this->arg1, &this->count1, &this->count_point1);
			convert_to_digit(this->memory, this->arg1, &this->count1, &this->count_point1);
		}
		else
		{
			clear_array(this->arg2, &this->count2, &this->count_point2);
			convert_to_digit(this->memory, this->arg2, &this->count2, &this->count_point2);
		}

		this->mrcFlag = 1;

		break;
	case MEMORY_SUBTRACTION:
		setOperands(this->count1, this->count2);
		if (this->count2 > 0)
		{
			this->memory -= convert_to_operands(this->arg2, this->count2, this->count_point2);
		}
		else if (this->count1 > 0)
		{
			this->memory -= convert_to_operands(this->arg1, this->count1, this->count_point1);
		}

		break;
	case MEMORY_ADDITION:
		setOperands(this->count1, this->count2);
		if (this->count2 > 0)
		{
			this->memory += convert_to_operands(this->arg2, this->count2, this->count_point2);
		}
		else if (this->count1 > 0)
		{
			this->memory += convert_to_operands(this->arg1, this->count1, this->count_point1);
		}

		break;
	case DECIMAL_SEPARATOR:
		if(this->op == NONE)
		{
			if (this->count_point1 == MAX_DIGITS) this->count_point1 = this->count1;
		}
		else
		{
			if (this->count_point2 == MAX_DIGITS) this->count_point2 = this->count2;
		}
	default:
		break;
	}
	call_display();
}
