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
    k1.addKey(&key17);
    k1.addKey(&key18);
    k1.addKey(&key19);
    
    key1.press(); 
    key3.press(); 
    key18.press();
    key11.press(); 
    key3.press();
    key19.press();
    key17.press(); 
    key16.press(); 
}