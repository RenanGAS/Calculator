#pragma once

#include "calculator.h"

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

	void left_align(int);
	void clear_array(Digit *, int *, int *);
	int convert_to_int(Digit *, int);
	int convert_to_digit(int, Digit *, int *);
	void call_display();
	void error_handle();
	void Operate();
	void setOperands(int, int);

public:
    NossaCpu();
	~NossaCpu();
    void setDisplay(Display *);
	void receiveDigit(Digit);
	void receiveOperation(Operation);
	void receiveControl(Control);
};