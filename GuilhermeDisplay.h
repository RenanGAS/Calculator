#pragma once

#include "calculator.h"

class GuilhermeDisplay : public Display
{
public:
	void add(Digit);
	void setDecimalSeparator();
	void setSignal(Signal);
	void setError();
	void clear();
};