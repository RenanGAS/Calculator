#include "NossaCpu.h"
#include <iostream>
#include <cmath>

#define TEST 0
#define MAX_DIGITS 8

// Class Cpu methods

// makes the number "complete" as in ready to operate
void NossaCpu::right_align(int arg)
{
	// TODO: accomodate the floating point
	int count;
	Digit *array;
	int helper;

	if (count + 1 > MAX_DIGITS)
	{
		return;
	}

	if (arg == 2)
	{
		helper = this->count2; // number of digits in the number
		array = this->arg2;
		count = this->count2;
	}
	else
	{
		helper = this->count1;
		array = this->arg1;
		count = this->count1;
	}


	if (arg == 2)
	{
		for (int i = (this->count2 -1); i <= 0; i--) // transfers the numbers to the rightmost side
		{
			this->arg2[MAX_DIGITS - this->count2 + i] = this->arg2[i];
			this->arg2[i] = ZERO;
			std::cout << "%d, %d\n", (MAX_DIGITS - 1 - this->count2 + i), i;
		}
		this->count2 = MAX_DIGITS;
	}
	else
	{
		for (int i = (this->count1 - 1); i <= 0; i++)
		{
			this->arg1[MAX_DIGITS - this->count1 + i] = this->arg1[i];
			this->arg1[i] = ZERO;
		}

		this->count1 = MAX_DIGITS;
	}
}
//clears an array of digits
void NossaCpu::clear_array(Digit *array, int* count, int* decimal_count, int signal_flag)
{
	for (int i = 0; i < MAX_DIGITS; i++)
	{
		array[i] = Digit(ZERO);
	}

	*count = 0;
	*decimal_count = MAX_DIGITS;
	if (signal_flag)
	{
		this->signal = POSITIVE;
	}
	
}

int NossaCpu::calculate_offset()
{
	if (this->count1 > this->count2)
	{
		return (this->count1 - this->count2);
	}
	else
	{
		return (this->count2 - this->count1);
	}
	
}

//transforms a single digit in a single int
int NossaCpu::digit_to_int(Digit digit)
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

Digit NossaCpu::int_to_digit(int number)
{
	switch (number)
	{
	case 0:
		return Digit(ZERO);
	case 1:
		return Digit(ONE);
	case 2:
		return Digit(TWO);
	case 3:
		return Digit(THRE);
	case 4:
		return Digit(FOUR);
	case 5:
		return Digit(FIVE);
	case 6:
		return Digit(SIX);
	case 7:	
		return Digit(SEVEN);
	case 8:
		return Digit(EIGHT);
	case 9:
		return Digit(NINE);
	default:
		return Digit(ZERO);
	}
}


//Convert a finished array of digits to an double to accomodate floating points
double NossaCpu::convert_to_operands(Digit *arg, int count, int offset)
{
	double result = 0;
	int digit;
	for (int i = 0; i < count; i++)
	{
		digit = this->digit_to_int(arg[i]);
		result += digit * pow(10, count - i + offset);
	}
	return result;
}


//obsolete
/* //converts a finished array of digits to a number
int NossaCpu::convert_to_int(Digit *arg, int count)
{
	//obsolete
	int result = 0;
	int digit;
	for (int i = 0; i < count; i++)
	{
		digit = this->digit_to_int(arg[i]);
		result += digit * pow(10, count - i - 1);
	}
	return result;
} */

//converts a number to a finished array of digits
int NossaCpu::convert_to_digit(double result, Digit * vet, int * count)
{
	int i = 0;
	count = 0;
	if (result < 0)
	{
		result = -result;
		//TODO: check case of MEMORY_READ_CLEAR
	if ((vet == this->arg1))
	{
		this->signal = NEGATIVE;
	}
	}
	int zero_checker = 0;
	while (result != 0)
	{
		if (i > MAX_DIGITS)
		{
			break;
		}
		Digit digit = int_to_digit((result / pow(10, MAX_DIGITS - i)));
		if ((digit != ZERO)) zero_checker = 1;
		vet[i] = digit;
		if(zero_checker)
		{
			if(digit == ZERO) count -= 1;
		}
		printf(" v[%d] = %d", i, digit);
		result =  fmod(result, pow(10, MAX_DIGITS - i));
		i++;
	}
	count += i;
	return 0;
}

//deprecated
/* converts a number to an array of digits and returns the 1 if the number is too big
int NossaCpu::convert_to_digit(int num, Digit *result, int *count)
{
	int i = MAX_DIGITS - 1;

	while (num != 0)
	{
		if (i < 0)
		{
			return 1;
			// HANDLING ERRORS
		}

		result[i] = Digit(num % 10);
		num /= 10;
		i--;
	}

	*count = MAX_DIGITS;

	return 0;
} */

// contains all the logic to call the display methods
void NossaCpu::call_display()
{

	if (this->signal == NEGATIVE) std::cout << "-";
	if (this->display == NULL)
		return;

	int zero_checker = 0;
	
	for (int i = 0; i < this->count1; i++)
	{
		if (((arg1[i] != 0) || zero_checker) && !(this->count2))
		{
			if (i == this->count_point1) 
			{
				this->display->setDecimalSeparator();
			}
			//TODO: check errors displaying zeros after dot
			this->display->add(arg1[i]);
			zero_checker = 1;
		}
	}

	for (int i = 0; i < this->count2; i++)
	{
		if ((arg2[i] != 0) || zero_checker)
		{
			if (i == this->count_point2) 
			{
				this->display->setDecimalSeparator();
			}
			this->display->add(arg2[i]);
			zero_checker = 1;
		}
	}
	std::cout << "\n";
}

// handles errors and displays them
void NossaCpu::error_handle()
{
	clear_array(this->arg1, &this->count1, &this->count_point1, 1);
	clear_array(this->arg2, &this->count2, &this->count_point2, 0);
	if (this->display != NULL)
		this->display->setError();
}

void NossaCpu::setOperands(int count1, int count2)
{
	if (count1 > 0 && count1 != MAX_DIGITS)
	{
		right_align(1);
	}

	if (count2 > 0 && count2 != MAX_DIGITS)
	{
		right_align(2);
	}
}

// takes the numbers and the operation and performs the operation
void NossaCpu::Operate()
{
	//TODO: something is wrong. Fix
	int offset = this->calculate_offset();
	double operand1, operand2;
	int point_counter;
	if(this->op == SQUARE_ROOT)
	{
		operand1 = convert_to_operands(this->arg1, this->count1, 0);
		operand2 = 0;
	}
	else if(this->count1 > this->count2)
	{
		operand1 = this->convert_to_operands(this->arg1, this->count1, offset);
		operand2 = this->convert_to_operands(this->arg2, this->count2, 0);
		point_counter = this->count_point2;
	}
	else
	{
		operand1 = this->convert_to_operands(this->arg1, this->count1, 0);
		operand2 = this->convert_to_operands(this->arg2, this->count2, offset);
		point_counter = this->count_point1;
	}
	//TODO: check if necessary
	/* 
	if (this->signal == NEGATIVE)
	{
		operand1 *= -1;
	} */
	
	//int operand1 = this->convert_to_int(this->arg1, this->count1);
	//int operand2 = this->convert_to_int(this->arg2, this->count2);
	double result = 0;
	//TODO: operate with number of decimal digits
	switch (this->op)
	{
	case ADDITION:
		result = operand1 + operand2;
		// DONE: check if the result is bigger than MAX_DIGITS
		break;
	case SUBTRACTION:
		result = operand1 - operand2;
		break;
	case MULTIPLICATION:
		result = operand1 * operand2;
		// DONE: check if the result is bigger than MAX_DIGITS
		break;
	case DIVISION:
		if (operand2 == 0)
			this->error_handle();
		else
			result = operand1 / operand2;
			//TODO: might lose precision (because of the double), if its a problem, change it
		// DONE: check if operand2 is 0
		break;
	case SQUARE_ROOT:
		// DONE: check if operand1 is negative
		if (operand1 > 0)
		{
			result = sqrt(operand1);
			//TODO: might lose precision (because of the double), if its a problem, change it
		}
		else
		{
			this->error_handle();
		}
		break;
	case PERCENTAGE:
		//result = operand1 / 100;
		//this may cause floats to appear
		//DONE: just ajust the floating point counter
		if (point_counter < 7)
		{
			point_counter += 2;
		}
		else this->error_handle();
		break;
	}

	clear_array(this->arg1, &this->count1, &this->count_point1, 1);

	//this is not in use. cant figure out how to know if a number has ended yet or not
	if (this->convert_to_digit(result, this->arg1, &this->count1))
	{
		this->error_handle();
	}
	this->count_point1 = point_counter;

	clear_array(this->arg2, &this->count2, &this->count_point2, 0);
}

// constructs the cpu
NossaCpu::NossaCpu()
{
	this->arg1 = static_cast<Digit *>(calloc(MAX_DIGITS, sizeof(Digit)));
	this->arg2 = static_cast<Digit *>(calloc(MAX_DIGITS, sizeof(Digit)));
	//this->op = NONE;
	this->count1 = 0;
	this->count2 = 0;
	this->count_point1 = MAX_DIGITS;
	this->count_point2 = MAX_DIGITS;
	this->display = NULL;
	this->memory = 0;
	this->mrcFlag = 0;
	this->signal = Signal(POSITIVE);
}

// destructs the cpu and frees the dinamically allocated arrays
NossaCpu::~NossaCpu()
{
	free(this->arg1);
	free(this->arg2);
}

// connects a display to the cpu
void NossaCpu::setDisplay(Display *display)
{
	this->display = display;
}

// contains the logic to receive the digits and put them in the correct array
void NossaCpu::receiveDigit(Digit d)
{
	//TODO: if digit is remaining from a operation, must be substituted when a new digit arrives
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

// contains the logic to receive the operations and operate if needed
void NossaCpu::receiveOperation(Operation op)
{
	this->op = op;

	// If the user press the SUBTRACTION Key just after ON/CE, the operand 1 will be negative
	if (this->op == 1 && this->count1 == 0)
	{
		this->signal = Signal(NEGATIVE);
	}
	
	setOperands(this->count1, this->count2);

	this->display->setSignal(this->signal);
	call_display();
}

// receive the control digit and treat appropriately
void NossaCpu::receiveControl(Control c)
{
	switch (c)
	{
	case EQUAL:
		setOperands(this->count1, this->count2);
		Operate();
		break;
	case CLEAR:
		// TODO: implement clear
		break;
	case RESET:
		clear_array(this->arg1, &this->count1, &this->count_point2, 1);
		clear_array(this->arg2, &this->count2, &this->count_point2, 0);
		this->count1 = 0;
		this->count2 = 0;
		// TODO: make the changes needed to acommodate floats
		break;
	case MEMORY_READ_CLEAR:
		setOperands(this->count1, this->count2);

		if (this->mrcFlag)
		{
			// TODO: Implement a flag that disappears when MEMORY_CLEAR is used.
			this->mrcFlag = 0;
			break;
		}
		
		if (this->count2 > 0)
		{
			clear_array(this->arg2, &this->count2, &this->count_point2, 0);
			convert_to_digit(this->memory, this->arg2, &this->count2);
			//
		}
		else
		{
			if (this->count1 > 0)
			{
				clear_array(this->arg1, &this->count1, &this->count_point1, 1);
			}
			convert_to_digit(this->memory, this->arg1, &this->count1);
		}
		this->mrcFlag = 1;

		break;
	case MEMORY_SUBTRACTION:
		setOperands(this->count1, this->count2);
		if (this->count2 > 0)
		{
			this->memory -= int(this->arg2[MAX_DIGITS - 1]);
		}
		else if (this->count1 > 0)
		{
			this->memory -= int(this->arg1[MAX_DIGITS - 1]);
		}

		// TODO: Implement a flag that disappears when MEMORY_SUBTRACTION sets the memory to zero.
		break;
	case MEMORY_ADDITION:
		setOperands(this->count1, this->count2);
		if (this->count2 > 0)
		{
			this->memory += int(this->arg2[MAX_DIGITS - 1]);
		}
		else if (this->count1 > 0)
		{
			this->memory += int(this->arg1[MAX_DIGITS - 1]);
		}

		// TODO: Implement a flag that appears when MEMORY_ADDITION is used.
		break;
	case DECIMAL_SEPARATOR:
		if (count1 > 0 && count1 != MAX_DIGITS && (!this->count_point1))
		{
			this->count_point1 = this->count1;
		}
		else if (!this->count_point2)
		{
			this->count_point2 = this->count2;
		}
		// TODO: test
		break;
	default:
		break;
	}

	this->display->setSignal(this->signal);
	call_display();
}
