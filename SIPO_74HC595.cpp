#include <Arduino.h>
#include "SoftataDevice_actuator.h"

Sipo74hc95::Sipo74hc95()
{
    Setup();
}

Sipo74hc95::Sipo74hc95(byte * settings)
{
    Setup(settings,NUM_SETTINGS);
}

bool Sipo74hc95::Setup()
{
  ic595 = new IC_74HC595_ShiftRegister();
  num_bytes = 1;
  return true;
}

bool Sipo74hc95::Setup(byte * settings, byte numSettings)
{
  ic595 = new IC_74HC595_ShiftRegister(settings,numSettings);
  if(num_settings>3)
    num_bytes = settings[3];
  return true;
}

int Sipo74hc95::GetNumBits()
{
    return num_bits;
}

int Sipo74hc95::GetInstanceValueRange()
{
    return SIPO_74HC595_MAX;
}

byte Sipo74hc95::GetActuatorCapabilities()
{
    return (byte)(a_bit | a_writebyte);
}

/*String  Sipo74hc95::GetPins()
{
    String msg = "SIPO_74HC595 Pins:";
    msg.concat(SIPO_74HC595_PINOUT);
    return msg;
}*/

// Index for if there are an array of actuators here.
// Instance of is collected elsewhere.
// No longer need. 2Do Remove

Tristate Sipo74hc95::Write(double value, int index)
{
    return notImplemented;
}

Tristate Sipo74hc95::Write(int value, int index, int numBytes )
{
    ic595->Write(value,numBytes);
    return (Tristate)true;
}


Tristate Sipo74hc95::SetBitState(bool state,int bitNo)
{
    ic595->SetBitState(state,bitNo);
    return (Tristate)true;
}

Tristate Sipo74hc95::SetBit(int bitNo )
{
    ic595->SetBit(bitNo);
    return (Tristate)true;
}

Tristate Sipo74hc95::ClearBit(int bitNo)
{
    ic595->ClearBit(bitNo);
    return (Tristate)true;
}

Tristate Sipo74hc95::ToggleBit(int bitNo)
{
    ic595->ToggleBit(bitNo);
    return (Tristate)true;
}