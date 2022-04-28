#pragma once

#include "calculator.h"
#include "NossoDisplay.h"

class NossaCpu : public Cpu
{
    Display *display;
	Digit *arg1;
	int count1;
	int count_point1;
	Operation op;
	Digit *arg2;
	int count2;
	int count_point2;
	int memory;
	int mrcFlag;
	Signal signal;
	Operation saveOp;
	//TODO: name the variables in the methods
	void right_align(int);
	void clear_array(Digit *, int *, int *);
	int convert_to_int(Digit *, int);
	void call_display();
	void error_handle();
	void Operate();
	void setOperands(int, int);
	int calculate_offset();
	int digit_to_int(Digit);
	Digit int_to_digit(int number);
	double convert_to_operands(Digit *, int, int);
	int convert_to_digit(double result, Digit * vet, int * count, int * decimal_count);
public:
    NossaCpu();
	~NossaCpu();
    void setDisplay(Display *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
};