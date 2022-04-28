#include "NossaCpu.h"
#include <iostream>
#include <cmath>

#define TEST 0
#define MAX_DIGITS 8

// Class Cpu methods

// makes the number "complete" as in ready to operate
void NossaCpu::right_align(int arg)
{
	int helper; //this is used to count without changing the count
	int *count; //this is used to change the count
	Digit** array; //this is used to change the array
	int* decimal_point; //this is used to change the decimal point
	if(arg == 2)
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
	if (helper + 1 > MAX_DIGITS) return;

	if (*decimal_point < MAX_DIGITS) *decimal_point = MAX_DIGITS - helper + *decimal_point; //this fixes the decimal point
	for (int i = (helper -1); i >= 0; i--) // transfers the numbers to the rightmost side
	{ //this for transfers from right to left in order to not overrwite any number
		(*array)[MAX_DIGITS - helper + i] = (*array)[i];
		(*array)[i] = ZERO;
	}
	*count = MAX_DIGITS;
}

//clears an array of digits
void NossaCpu::clear_array(Digit *array, int* count, int* decimal_count)
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

//TODO: check if this is necessary
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
double NossaCpu::convert_to_operands(Digit *arg, int count, int point_count)
{	
	double result = 0;
	int digit;
	for (int i = 0; i < count; i++)
	{
		digit = digit_to_int(arg[i]);
		result += digit * pow(10, point_count - i -1);
	}
	return result;
}

//converts a number to a finished array of digits
int NossaCpu::convert_to_digit(double result, Digit * vet, int * count, int * decimal_count)
{
	Digit digito;
	int i = 0;
	int zero_checker = 0;
	*count = 0;
	*decimal_count = 0;
	if (result < 0)
	{
		result = -result;
		//TODO: check case of MEMORY_READ_CLEAR
		if (vet == this->arg1)
		{
			this->signal = NEGATIVE;
		}
	}
	double result_helper = result;

	//TODO: calculate decimal place
	while (result_helper > 1)
	{
		result_helper /= 10;
		(*decimal_count)++;
		if(*decimal_count > MAX_DIGITS)
		{
			return 1;
		}
	}


	while (result != 0)
	{
		if (*count == MAX_DIGITS)
		{
			break;
		}
		Digit digit = int_to_digit((result / pow(10, MAX_DIGITS - i)));
		if ((digit != ZERO)) zero_checker = 1;
		if(zero_checker)
		{
			vet[*count] = digit;
			*count += 1;
		}
		printf(" v[%d] = %d", i, digit);
		result =  fmod(result, pow(10, MAX_DIGITS - i));
		i++;
	}
	printf("\n");
	return 0;
}


// contains all the logic to call the display methods
void NossaCpu::call_display()
{

	if (this->signal == NEGATIVE) std::cout << "-";
	if (this->display == NULL)
		return;

	int zero_checker = 0;
	printf("\n%d\n", this->count_point1);
	for (int i = 0; i < MAX_DIGITS; i++)
	{
		if (i == this->count_point1)
		{
			std::cout << ".";
		}
		this->display->add(this->arg1[i]);
	}
	std::cout << "\n";
	for (int i = 0; i < MAX_DIGITS; i++)
	{
		if (i == this->count_point2)
		{
			std::cout << ".";
		}
		this->display->add(this->arg2[i]);
	}
	

	/* for (int i = 0; i < this->count1; i++)
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
	} */
	/* 
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
	} */
	std::cout << "\n";
}

// handles errors and displays them
void NossaCpu::error_handle()
{
	clear_array(this->arg1, &this->count1, &this->count_point1);
	clear_array(this->arg2, &this->count2, &this->count_point2);
	if (this->display != NULL)
		this->display->setError();
}

void NossaCpu::setOperands(int count1, int count2)
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
void NossaCpu::Operate()
{
	//TODO: something is wrong. Fix
	int offset = this->calculate_offset();
	double operand1, operand2;
	operand1 = convert_to_operands(this->arg1, this->count1, this->count_point1);
	operand2 = convert_to_operands(this->arg2, this->count2, this->count_point2);
	std::cout << operand1 << " + " << operand2 << "\n";
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
		result = operand1 / 100;
		break;
	}

	clear_array(this->arg1, &this->count1, &this->count_point1);

	//this is not in use. cant figure out how to know if a number has ended yet or not
	if (this->convert_to_digit(result, this->arg1, &this->count1, &this->count_point1))
	{

		this->error_handle();
	}
	this->right_align(1);

	clear_array(this->arg2, &this->count2, &this->count_point2);
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
//TODO: change it
void NossaCpu::receiveOperation(Operation op)
{
	this->op = op;
	right_align(1);
	if (this->count2 > 0)
	{
		right_align(2);
	}
	// If the user press the SUBTRACTION Key just after ON/CE, the operand 1 will be negative
	if (this->op == 1 && this->count1 == 0)
	{
		this->signal = Signal(NEGATIVE);
	}
	
	setOperands(this->count1, this->count2);
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
		clear_array(this->arg1, &this->count1, &this->count_point2);
		clear_array(this->arg2, &this->count2, &this->count_point2);
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
			clear_array(this->arg2, &this->count2, &this->count_point2);
			convert_to_digit(this->memory, this->arg2, &this->count2, &this->count_point2);
		}
		else
		{
			if (this->count1 > 0)
			{
				clear_array(this->arg1, &this->count1, &this->count_point1);
			}
			convert_to_digit(this->memory, this->arg1, &this->count1, &this->count_point1);
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
