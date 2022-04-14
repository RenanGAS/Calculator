#ifndef CALC
#define CALC

#define MAX_DIGITS 8

// on teacher's there is a switch for digits with error option, even though it doesn't have it here
enum Digit {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ERROR};
enum Operation {ADDITION, SUBTRACTION, DIVISION, MULTIPLICATION, SQUARE_ROOT, PERCENTAGE, NONE};
enum Control {CLEAR, RESET, DECIMAL_SEPARATOR, MEMORY_READ, MEMORY_CLEAR, MEMORY_ADDITION, MEMORY_SUBTRACTION, EQUALS};

class Display
{
  public:
    void add(Digit );
    void add(Operation );
    void addDecimalSeparator();
    void clear();
};

class Receiver
{
  public:
    virtual void receiveDigit(Digit ) = 0;
    virtual void receiveOperation(Operation ) = 0;
    virtual void receiveControl(Control ) = 0;
};

class Cpu: public Receiver
{
    Display *display;
    Digit *arg1;
    int count1;
    Operation op;
    Digit *arg2;
    int count2;

    void left_align(int );
    void clear_array(Digit * );
    int convert_to_int(Digit * , int );
    int convert_to_digit(int , Digit * , int&);
    void call_display();
    void error_handle();
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

class Keyboard: public Receiver
{
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

class Key
{
   protected:
     Receiver* receiver;
   public:
      virtual void press() = 0;

      void setKeyboard(Keyboard* );
};

class KeyDigit: public Key
{
     Digit digit;
   public:
      KeyDigit(Digit );
      void press();
};

class KeyOperation: public Key
{
     Operation operation;
   public:
      KeyOperation(Operation );
      void press();
};

class KeyControl: public Key
{
     Control control;
   public:
      KeyControl(Control );
      void press();
};

#endif