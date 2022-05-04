#include "calculator.h"
#include "GuilhermeCpu.h"
#include "GuilhermeKeyboard.h"
#include "GuilhermeDisplay.h"
#include <iostream>

int main()
{
    GuilhermeDisplay display;
    GuilhermeCpu cpu;
    GuilhermeKeyboard k1;
    KeyDigit key0(ZERO), key1(ONE), key2(TWO), key3(THRE), key4(FOUR), key5(FIVE), key6(SIX), key7(SEVEN), key8(EIGHT), key9(NINE);
    KeyOperation keyaddition(ADDITION), keysubtraction(SUBTRACTION), keydivision(DIVISION), keymultiplication(MULTIPLICATION), keysqrt(SQUARE_ROOT), keypercentage(PERCENTAGE);
    KeyControl keyequal(EQUAL), key17(MEMORY_READ_CLEAR), key18(MEMORY_ADDITION), key19(MEMORY_SUBTRACTION), keyponto(DECIMAL_SEPARATOR);

    k1.setCpu(&cpu);
    cpu.setDisplay(&display);

    k1.addKey(&key0);
    k1.addKey(&key1);
    k1.addKey(&key2);
    k1.addKey(&key3);
    k1.addKey(&key4);
    k1.addKey(&key5);
    k1.addKey(&key6);
    k1.addKey(&key7);
    k1.addKey(&key8);
    k1.addKey(&key9);
    k1.addKey(&keyaddition);
    k1.addKey(&keysubtraction);
    k1.addKey(&keydivision);
    k1.addKey(&keymultiplication);
    k1.addKey(&keysqrt);
    k1.addKey(&keypercentage);
    k1.addKey(&keyequal);
    k1.addKey(&keyponto);
    k1.addKey(&key17);
    k1.addKey(&key18);
    k1.addKey(&key19);
    

    key1.press(); 
    key1.press();
    key1.press();
    key3.press();
    keyponto.press();
    key3.press();
    key3.press();
    keysubtraction.press();
    key1.press(); 
    key2.press();
    keyponto.press();
    key0.press();
    keyequal.press(); 
}