#include "display.h"
#include <iostream>
#include <cmath>

//Class Display methods

//adds a digit to the display
void NossoDisplay::add(Digit digit)
{
	//this is used to ensure the correct digit will be displayed even with a different order of the enum
	switch (digit)
	{
	case ZERO:
		std::cout << "0";
		break;
	case ONE:
		std::cout << "1";
		break;
	case TWO:
		std::cout << "2";
		break;
	case THREE:
		std::cout << "3";
		break;
	case FOUR:
		std::cout << "4";
		break;
	case FIVE:
		std::cout << "5";
		break;
	case SIX:
		std::cout << "6";
		break;
	case SEVEN:
		std::cout << "7";
		break;
	case EIGHT:
		std::cout << "8";
		break;
	case NINE:
		std::cout << "9";
		break;
	default:
		break;
	}
}

//adds a decimal separator to the display
void NossoDisplay::SetDecimalSeparator()
{
	std::cout << ".";
}

//Sets the signal of the number to be displayed
void NossoDisplay::setSignal(Signal signal)
{
	switch (signal)
	{
	case POSITIVE:
		//the calculator treats the absence of signal as positive
		break;
	case NEGATIVE:
		std::cout << "-";
		break;
	default:
		break;
	};
}

//Sets a error message
void NossoDisplay::setError()
{
	std::cout << "Error" << std::endl;
}

//clears the display
void NossoDisplay::clear()
{
	std::cout << "\n";
}