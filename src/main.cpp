#include "calculator.hpp"

int main()
{
    Display display;
    Cpu cpu(&display);
    Keyboard k1(&cpu);
    Digit_key key0(ZERO), key1(ONE);
    Operation_Key key2(PLUS);

    k1.addKey(&key0);
    k1.addKey(&key1);
    k1.addKey(&key2);
    key0.press();
    key2.press();
    key1.press();
    key2.press();

}