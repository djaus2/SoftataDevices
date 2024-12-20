#include <Arduino.h>
#include "ic_74hc595_shiftRegister.h"

//Ref: https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/
//     https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/

        int datapin = 16;  
        int latchPin = 20;
        int clockPin = 21;
        unsigned int value = 0;

void write595(BitOrder order, unsigned int data, int numBytes = 1 ) 
{
  // Output low level to latchPin
    digitalWrite(latchPin, LOW);

    // Send serial data to 74HC595
    if(numBytes==1)
    {
        shiftOut(datapin, clockPin, order, data);
    }
    else if (numBytes==2)
    {
        if(order == MSBFIRST)
        {
            // shift out high byte
            shiftOut(datapin, clockPin, order, (data >> 8));
            // shift out low byte
            shiftOut(datapin, clockPin, order, data);
        }
        else
        {
            // shift out low byte
            shiftOut(datapin, clockPin, order, data);
            // shift out high byte
            shiftOut(datapin, clockPin, order, (data >> 8));
        }
    }
    // Output high level to latchPin, and 74HC595 will update the data to the parallel output port.
    digitalWrite(latchPin, HIGH);
    value = data;
}


bool IC_74HC595_ShiftRegister::Setup()
{
  datapin = 16;  
  latchPin = 20;
  clockPin = 21;
  return Setup(NULL,0);
}

bool IC_74HC595_ShiftRegister::Setup(byte * settings, byte numSettings)
{
  if (numSettings >0)
  {
    datapin = (int)settings[0];
    if (numSettings >1)
    {
        latchPin = (int)settings[1];
        if (numSettings >2)
        {
            clockPin = (int)settings[2];
        };
    };
  };
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(datapin, OUTPUT);
  value = 0;
  write595(LSBFIRST, value);
  return true;
}


// Default Setup
IC_74HC595_ShiftRegister::IC_74HC595_ShiftRegister()
{
  Setup();
}

IC_74HC595_ShiftRegister::IC_74HC595_ShiftRegister(byte * settings, byte numSettings)
{
  Setup(settings,numSettings);
}


bool IC_74HC595_ShiftRegister::Write(unsigned int num, int numBytes)
{
  write595(LSBFIRST, num, numBytes);
  return true;
}


// Thse bit manipulations are only 8 bit not 16.
bool IC_74HC595_ShiftRegister::SetBitState(bool state,int bitNo)
{
    byte mask = 1 << bitNo;
    if (state)
    {
        value |= mask;
    }
    else
    {
        value &= ~mask;
    }
    write595(LSBFIRST, value);
    return true;
}


bool IC_74HC595_ShiftRegister::SetBit(int bitNo)
{
    byte mask = 1 << bitNo;
    value |= mask;
    write595(LSBFIRST, value);
    return true;
}

bool IC_74HC595_ShiftRegister::ClearBit(int bitNo)
{
    byte mask = 1 << bitNo;
    value &= ~mask;
    write595(LSBFIRST, value);
    return true;
}

bool IC_74HC595_ShiftRegister::ToggleBit(int bitNo)
{
    byte mask = 1 << bitNo;
    value ^= mask;
    write595(LSBFIRST, value);
    return true;
}

bool IC_74HC595_ShiftRegister::SetLevel(int level)
{
    write595(LSBFIRST, level);
    return true;
}