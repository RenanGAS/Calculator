#pragma once

#include "calculator.h"

class NossoDisplay : public Display
{
public:
	void add(Digit);
	void SetDecimalSeparator();
	void setSignal(Signal);
	void setError();
	void clear();
};