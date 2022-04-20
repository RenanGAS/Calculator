#include "calculator.h"
#include "cpu.h"
#include "keyboard.h"
#include "keys.h"
#include "display.h"
#include <iostream>

int main()
{
    NossoDisplay display;
    NossaCpu cpu;
    NossoKeyboard k1;
    NossaKeyDigit key0(ZERO), key1(ONE), key2(TWO), key3(THREE), key4(FOUR), key5(FIVE), key6(SIX), key7(SEVEN), key8(EIGHT), key9(NINE);
    NossaKeyOperation key10(ADDITION), key11(SUBTRACTION), key12(DIVISION), key13(MULTIPLICATION), key14(SQUARE_ROOT), key15(PERCENTAGE);
    NossaKeyControl key16(EQUALS);

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
    k1.addKey(&key10);
    k1.addKey(&key11);
    k1.addKey(&key12);
    k1.addKey(&key13);
    k1.addKey(&key14);
    k1.addKey(&key15);
    k1.addKey(&key16);
    
    key1.press(); // um
    std::cout << "       .1\n";
    key3.press(); // três
    std::cout << "       .2\n";
    key10.press(); // +
    std::cout << "       .3\n";
    key2.press(); // dois
    std::cout << "       .4\n";
    key16.press(); // igual
    std::cout << "       .5\n";
}