#include "calculator.hpp"

int main()
{
    Keyboard k1;
    Key key0(ZERO), key1(ONE);

    k1.addKey(&key0);
    k1.addKey(&key1);
}