#pragma once

#include "calculator.h"

class OurDisplay : public Display
{
public:
	void add(Digit);
	void setDecimalSeparator();
	void setSignal(Signal);
	void setError();
	void clear();
};