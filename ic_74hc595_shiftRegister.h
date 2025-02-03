#ifndef IC_74HC595_ShitRegisterH
#define IC_74HC595_ShitRegisterH

// Ref: https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/
//      https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/



class IC_74HC595_ShiftRegister
{

  public:
      IC_74HC595_ShiftRegister();
      IC_74HC595_ShiftRegister(byte * settings, byte numSettings);
      bool Setup();
      bool Setup(byte * settings, byte numSettings);
      virtual bool SetBitState(bool state,word index);
      virtual bool SetBit(word index );
      virtual bool ClearBit(word index );
      virtual bool ToggleBit(word index );
      virtual bool SetLevel(int level );
      virtual bool Write(word num, word numBytes=1);
      // Can daisy chain two 74HC595s as per top link. //Assume data is 16 bits
  private:
      virtual void write595(word data, int numBytes = 1 );
      int dataPin = 16;  
      int latchPin = 20;
      int clockPin = 21;
      word numBytes = 1;
      word numBits = 8;
      BitOrder order = LSBFIRST;
      word value = 0;
};

#endif