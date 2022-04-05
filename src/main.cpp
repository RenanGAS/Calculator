#include "calculator.hpp"
using namespace std;

int main()
{
    Keyboards *kb;
    Buttons *bt;

    

    OpButtons *opB;
    ControlButtons *ctrlB;

    Digits *dgs;
    DigitButtons *dgBt0;

    dgBt0->setDigit(dgs[0]);

    opB->setOperation();
    bt->setKeyboard(kb);
    kb->setButtons();
    return EXIT_SUCCESS;
}
