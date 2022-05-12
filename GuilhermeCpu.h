#pragma once

#include "calculator.h"
#include "GuilhermeDisplay.h"

class GuilhermeCpu : public Cpu
{
	Digit *arg1;
	int count1;
	int count_point1;
	Operation op;
	Digit *arg2;
	int count2;
	int count_point2;
	double memory;
	int mrcFlag;
	Signal signal;
	Operation saveOp;
	Digit* argequal;
	int countequal;
	int countpointequal;
	void right_align(int arg);
	void clear_array(Digit *array, int *count, int *decimal_count);
	void call_display();
	void error_handle();
	void Operate();
	void setOperands(int count1, int count2);
	int digit_to_int(Digit digit);
	Digit int_to_digit(int number);
	double convert_to_operands(Digit *arg, int count, int point_count);
	int convert_to_digit(double result, Digit * vet, int * count, int * decimal_count);
public:
    GuilhermeCpu();
	~GuilhermeCpu();
    void setDisplay(Display *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
};