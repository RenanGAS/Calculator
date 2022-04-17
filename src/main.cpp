#include "calculator.h"
#include <iostream>

int main()
{
    Display display;
    Cpu cpu;
    Keyboard k1;
    KeyDigit key0(TWO), key1(ONE);
    KeyOperation key2(ADDITION);

    k1.setCpu(&cpu);
    cpu.setDisplay(&display);
    k1.addKey(&key0);
    k1.addKey(&key1);
    k1.addKey(&key2);
    key0.press();
    std::cout << "   .1\n";
    key2.press();
    std::cout << "   .2\n";
    key1.press();
    std::cout << "   .3\n";
    key2.press();
    std::cout << "   .4\n";

}