#include "calculator.hpp"

int main()
{
    Display display;
    Cpu cpu(&display);
    Keyboard k1(&cpu);
    Digit_key key0(TWO), key1(ONE);
    Operation_Key key2(PLUS);

    k1.addKey(&key0);
    k1.addKey(&key1);
    k1.addKey(&key2);
    key0.press();
    printf("   .1\n");
    key2.press();
    printf("   .2\n");
    key1.press();
    printf("   .3\n");
    key2.press();
    printf("   .4\n");

}