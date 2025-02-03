#include <Arduino.h>
#include "ic_74hc595_shiftRegister.h"

//Ref: https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/
//     https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/



void IC_74HC595_ShiftRegister::write595(word data, int numBytes ) 
{
  // Output low level to latchPin
    digitalWrite(latchPin, LOW);

    // Send serial data to 74HC595
    if(numBytes==1)
    {
        shiftOut(dataPin, clockPin, order, data); //*************
    }
    else if (numBytes==2)
    {
        if(order == MSBFIRST)
        {
            // shift out high byte
            shiftOut(dataPin, clockPin, order, (data >> 8)); 
            // shift out low byte
            shiftOut(dataPin, clockPin, order, (data & 0xff));
        }
        else
        {
            // shift out low byte
            shiftOut(dataPin, clockPin, order, (data & 0xff)); 
            // shift out high byte
            shiftOut(dataPin, clockPin, order, (data >> 8));
        }
    }
    // Output high level to latchPin, and 74HC595 will update the data to the parallel output port.
    digitalWrite(latchPin, HIGH);
    value = data; 
}


bool IC_74HC595_ShiftRegister::Setup()
{
  dataPin = 16;  
  latchPin = 20;
  clockPin = 21;
  numBytes = 1;
  numBits = 8;
  order = LSBFIRST;
  return Setup(NULL,0);
}

bool IC_74HC595_ShiftRegister::Setup(byte * settings, byte numSettings)
{
  if (numSettings >0)
  {
    dataPin = (int)settings[0];
    if (numSettings >1)
    {
        latchPin = (int)settings[1];
        if (numSettings >2)
        {
            clockPin = (int)settings[2];
             if (numSettings >3)
            {
                numBytes = (int)settings[3];   
                if (numSettings >4)
                {
                    order = (BitOrder)settings[4];
                } 
            };
        }
    };
  };
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  value = 0;
  write595(order, value);
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


bool IC_74HC595_ShiftRegister::Write(word num, word numBytes)
{
  write595(num, numBytes);
  return true;
}



bool IC_74HC595_ShiftRegister::SetBitState(bool state,word bitNo)
{
    if( bitNo > (numBits-1) )
      return false;
    word mask = 1 << bitNo;
    if (state)
    {
        value |= mask;
    }
    else
    {
        value &= ~mask;
    }
    write595(value);
    return true;
}


bool IC_74HC595_ShiftRegister::SetBit(word bitNo)
{
    if( bitNo > (numBits-1) )
      return false;
    word mask = 1 << bitNo;
    value |= mask;
    write595( value);
    return true;
}

bool IC_74HC595_ShiftRegister::ClearBit(word bitNo)
{
    if( bitNo > (numBits-1) )
      return false;
    word mask = 1 << bitNo;
    value &= ~mask;
    write595(value);
    return true;
}

bool IC_74HC595_ShiftRegister::ToggleBit(word bitNo)
{
    if( bitNo > (numBits-1) )
      return false;
    word mask = 1 << bitNo;
    value ^= mask;
    write595(value);
    return true;
}

bool IC_74HC595_ShiftRegister::SetLevel(int level)
{
    write595(order, level);
    return true;
}