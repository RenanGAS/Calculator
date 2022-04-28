#include "calculator.h"
#include "NossaCpu.h"
#include "NossoKeyboard.h"
#include "NossoDisplay.h"
#include <iostream>

int main()
{
    NossoDisplay display;
    NossaCpu cpu;
    NossoKeyboard k1;
    KeyDigit key0(ZERO), key1(ONE), key2(TWO), key3(THRE), key4(FOUR), key5(FIVE), key6(SIX), key7(SEVEN), key8(EIGHT), key9(NINE);
    KeyOperation key10(ADDITION), key11(SUBTRACTION), key12(DIVISION), key13(MULTIPLICATION), key14(SQUARE_ROOT), key15(PERCENTAGE);
    KeyControl key16(EQUAL), key17(MEMORY_READ_CLEAR), key18(MEMORY_ADDITION), key19(MEMORY_SUBTRACTION);

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
    
    std::cout << "\n1.";
    key1.press(); // um
    std::cout << "\n2.";
    key3.press(); // três
    std::cout << "\n3.";
    key15.press(); // +
    std::cout << "\n4.";
    key2.press(); // dois
    std::cout << "\n5.";
    key15.press(); // %
}