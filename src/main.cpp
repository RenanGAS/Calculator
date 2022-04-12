#include "calculator.h"
#include "calculator.cpp"
#include <iostream>
#include <cstring>
using namespace std;

void limpatela(char **s)
{
    delete *s;
}

int main()
{
    Keyboard *kb = new Keyboard();
    Cpu *cp = new Cpu();
    Display *dp = new Display();
    Calculator calc;

    calc.setKeyboard(kb);
    calc.setCpu(cp);
    calc.setDisplay(dp);

    // Funciona:
    // if (calc.kb->bt[2]->getValue() == 2)
    // {
    //     int x = calc.kb->bt[2]->getValue();
    //     cout << "\nbt[2]->getValue() = " << x << "\n";
    // }

    calc.run();

    return EXIT_SUCCESS;
}
