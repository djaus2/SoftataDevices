#include <Arduino.h>
#include "SoftataDevice_deviceinput.h"

#include "ic_74hc165_shiftRegister.h"

Piso74HC165::Piso74HC165()
{
   Setup();
}

Piso74HC165::Piso74HC165(int pin)
{
    byte _pin= pin;
    Setup(&_pin,1);
}


bool Piso74HC165::Setup()
{
  ic165 = new IC_74HC165_ShiftRegister();
  num_bytes = 1;
  return true;
}

bool Piso74HC165::Setup(byte * settings, byte numSettings)
{

  ic165 = new IC_74HC165_ShiftRegister(settings,numSettings);
  if(num_settings>3)
    num_bytes = settings[3];
  return true;
}

int Piso74HC165::GetNumBits()
{
    Serial.print("Piso74HC165::GetNumBits(): ");
    Serial.println(num_bits);
    return num_bits;
}

int Piso74HC165::GetInstanceValueRange()
{
    return SHIFTIN_74HC165_MAX;
}

byte Piso74HC165::GetInputCapabilities()
{
    byte capab = i_bit | i_readbyte | i_readword ;
    return capab;
}

/*String Piso74HC165::GetPins()
{
    String msg = "Relay Pins";
    msg.concat(RELAY_PINOUT);
    return msg;
}*/

// Index for if there are an array of actuators here.
// Instance of is collected elsewhere.
// No longer need. 2Do Remove


word Piso74HC165::readWord()
{
  return ic165->read165(2);
}

byte Piso74HC165::readByte()
{
    word res =  ic165->read165(1);
    return (byte) res ;
}


bool Piso74HC165::PollBit(byte bitNo) 
{
    Serial.println("Getting Piso74HC165 Bit");
    return ic165->PollBit(bitNo);
}

