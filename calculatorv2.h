#ifndef CALC
#define CALC

#define MAX_DIGITS 8

enum Digit {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOT};
enum Operation {SUM, SUBTRACTION, MULTIPLICATION, DIVISION, SQRT, PERCENT, NONE};
enum Control {CLEAR, RESET, EQUALS, MRC, MMINUS, MPLUS, OFF};

class Display{
  public:
    void add(Digit );
    void add(Operation ); //not part of the standard shown,
    //but the only solution I found that seemed compliant enough
    void clear();
};

class Cpu{
    Display *display;
    Digit *arg1;
    int count1;
    Operation op;
    Digit *arg2;
    int count2;

    void left_align(int arg);
    void clear_array(Digit *array);
    int convert_to_int(Digit *arg, int count);
    void convert_to_digit(int arg, Digit *result);
    void call_display();
    void Operate();
  public:
    Cpu();
    ~Cpu();
    void setDisplay(Display* );
    void receiveDigit(Digit );
    void receiveOperation(Operation );
    void receiveControl(Control );
};

class Key;

class Keyboard{
   Key* keys[200];
   int KeysCount;
   Cpu* cpu;
   public:
      void setCpu(Cpu );
      
      void addKey(Key* );
      void receiveDigit(Digit );
      void receiveOperation(Operation );
      void receiveControl(Control );

};

class Key{
   protected:
     Keyboard* keyboard;
   public:
      virtual void press() = 0;

      void setKeyboard(Keyboard* );
};

class KeyDigit: public Key{
     Digit digit;
   public:
      KeyDigit(Digit );
      void press();
};

class KeyOperation: public Key{
     Operation operation;
   public:
      KeyOperation(Operation );
      void press();
};

class KeyControl: public Key{
     Control control;
   public:
      KeyControl(Control );
      void press();
};

#endif