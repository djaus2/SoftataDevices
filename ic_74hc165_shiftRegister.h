#ifndef IC_74HC165_ShitRegisterH
#define IC_74HC165_ShitRegisterH


// Ref: https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/ Need to change this
//      https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/



class IC_74HC165_ShiftRegister
{

  public:
      IC_74HC165_ShiftRegister();
      IC_74HC165_ShiftRegister(byte * settings, byte numSettings);
      bool Setup();
      bool Setup(byte * settings, byte numSettings);
      virtual bool PollBit(int bitNo);
      virtual word read165(byte numBytes);
      // Can daisy chain two 74HC165s as per top link. //Assume data is 8 bits
  private:  
      virtual byte readByte165();
      virtual word readWord165();
      int dataPin = 16;  
      int latchPin = 20;
      int clockPin = 21;
      int numBytes = 1;
      int numBits = 8;
      BitOrder order = LSBFIRST;
      word value = 0;

};

#endif