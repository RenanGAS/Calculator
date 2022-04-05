#include "calculator.hpp"

int main()
{
    Display display;
    Cpu cpu(&display);
    Keyboard k1(&cpu);
    Digit_key key0(ZERO), key1(ONE);

    k1.addKey(&key0);
    k1.addKey(&key1);
}