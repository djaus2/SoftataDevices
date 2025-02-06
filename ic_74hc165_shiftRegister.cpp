#include <Arduino.h>
#include "ic_74hc165_shiftRegister.h"

//Ref: https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/
//     https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
// https://docs.wokwi.com/parts/wokwi-74hc165 Example and discussion. Doesn't use Arduino shiftin function though
// https://d3mk240zzrnosz.cloudfront.net/assets/ZC4858_datasheetMain_40342.pdf
// Example circuit https://forum.arduino.cc/t/74hc165-shift-register-with-shiftin-wraps-last-bit-around-the-beginning/601084/3


bool IC_74HC165_ShiftRegister::Setup()
{
  dataPin = 16;   //Q7 Is data out from 165 to micro                165 Pin 9
  latchPin = 20;  //PL When low data is beung sampled. Hi latched   165 Pin 1
  clockPin = 21;  //CP Clock                                        165 Pin 2
                  // CE GND 165 (is enabled)                        165 Pin 15
                  // SE Serial for cascade input                    165 Pin 10
  numBytes = 1;
  numBits = 8*numBytes;
  BitOrder order = LSBFIRST;
  return Setup(NULL,0);
}

bool IC_74HC165_ShiftRegister::Setup(byte * settings, byte numSettings)
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
                if ((numBytes<1) || (numBytes>2))
                  return false;
                numBits = 8 * numBytes;
                if (numSettings >4)
                {
                    order = (BitOrder)settings[4];
                }
            }
        };
    };
  };

  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  pinMode(dataPin, INPUT);
  pinMode(latchPin, OUTPUT);
  digitalWrite(latchPin, HIGH);
  return true;
}


// Default Setup
IC_74HC165_ShiftRegister::IC_74HC165_ShiftRegister()
{
  Setup();
}

IC_74HC165_ShiftRegister::IC_74HC165_ShiftRegister(byte * settings, byte numSettings)
{
  Setup(settings,numSettings);
}

bool IC_74HC165_ShiftRegister::PollBit(int bitNo)
{
  if( bitNo > (numBits-1) )
    return false;
  word value = read165(numBytes);
  word mask = 1 << bitNo;
  value = value & mask;
  return (value > 0);
}

byte IC_74HC165_ShiftRegister::readByte165() 
{
  /*Edit: Okay it's a common problem between the 165 and the ShiftIn function. Including an
  digitalWrite(clockPin, HIGH);
  before setting the latchPin LOW solves it.
  https://forum.arduino.cc/t/two-daisy-chained-74hc165-can-t-detect-several-button-presses-at-once/186466/12
  */
   digitalWrite(clockPin, HIGH);

    digitalWrite(latchPin, LOW);
    delayMicroseconds(5);
    // Output high level to latchPin, and 74HC165 will update the data to be shifted in.
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(5);  
        //digitalWrite(clockEnablePin, LOW); Have anchored to GND
        byte value = shiftIn(dataPin, clockPin, order);
    Serial.println(value,HEX);
     return value;
}

word IC_74HC165_ShiftRegister::readWord165() 
{
  /*Edit: Okay it's a common problem between the 165 and the ShiftIn function. Including an
  digitalWrite(clockPin, HIGH);
  before setting the latchPin LOW solves it.
  https://forum.arduino.cc/t/two-daisy-chained-74hc165-can-t-detect-several-button-presses-at-once/186466/12
  */
    digitalWrite(clockPin, HIGH);

    digitalWrite(latchPin, LOW);
    delayMicroseconds(5);
    // Output high level to latchPin, and 74HC165 will update the data to be shifted in.
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(5);

    byte value1 = shiftIn(dataPin, clockPin, order);
    Serial.println(value1,HEX);
    byte value2 = shiftIn(dataPin, clockPin, order);

    if(order == MSBFIRST)
    {
        return value1 << 8 | value2;
    }
    else
    {
        return value2 << 8 | value1;
    }
    return value;
}

word IC_74HC165_ShiftRegister::read165(byte _numBytes ) 
{
   word value;
   byte value1,value2;
  // Output low level to latchPin
    if(_numBytes > numBytes)
      _numBytes = numBytes;
    else if(_numBytes<1)
      _numBytes =1;

    // Read in serial data via 74hc165
    if(_numBytes==1)
    {
        value = (word)readByte165();
    }
    else if (_numBytes==2)
    {
        value = readWord165();
    }
    return value;
}

/*
byte red()
{
    // Write pulse to load pin
  digitalWrite(latch, LOW);
  delayMicroseconds(5);
  digitalWrite(latch, HIGH);
  delayMicroseconds(5);
 
  // Get data from 74HC165
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);
  return incoming
}*/