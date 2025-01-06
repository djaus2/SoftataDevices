#include <Arduino.h>
#include "SoftataDevice_actuator.h"

SoftataDevice_QuadRelays::SoftataDevice_QuadRelays()
{
   
}

SoftataDevice_QuadRelays::SoftataDevice_QuadRelays(int pin)
{
    byte _relayPin = pin;
    Setup(&_relayPin,1);
}


bool SoftataDevice_QuadRelays::Setup()
{
  byte _relayPin = 16;
  Setup(&_relayPin,1);
  return true;
}

bool SoftataDevice_QuadRelays::Setup(byte * settings, byte numSettings)
{

  if(numSettings>0)
  {
    relayPin = settings[0];
  }
   else
   {
        Serial.print("Setting up QuadRelays FAILED: No settings (pin no.)");
        return false;
   }
    Serial.print("Setting up quadrelays on pins: ");
    Serial.print(relayPin);
    Serial.print(" to pin ");
    Serial.println(relayPin+3);
    for (int i=0;i<num_bits;i++)
    {
        pinMode(relayPin+i, OUTPUT);
        digitalWrite(relayPin+i, false);
    }
    return true;
}

int SoftataDevice_QuadRelays::GetNumBits()
{
    Serial.println("SoftataDevice_QuadRelays::GetNumBits()");
    return num_bits;
}

/*String SoftataDevice_QuadRelays::GetPins()
{
    String msg = "Relay Pins";
    msg.concat(RELAY_PINOUT);
    return msg;
}*/

// Index for if there are an array of actuators here.
// Instance of is collected elsewhere.
// No longer need. 2Do Remove

Tristate SoftataDevice_QuadRelays::Write(double value, int index)
{
    return notImplemented;
}

int SoftataDevice_QuadRelays::GetInstanceValueRange()
{
    return  pow(2,num_bits)-1;
}


Tristate SoftataDevice_QuadRelays::Write(int value, int index, int numBytes )
{
    int maxRange = GetInstanceValueRange();
    if(value >maxRange)
    {
        Serial.println("QuadRelays Write: Invalid  value");
        return invalidParams;
    }
    else if(value<0)
    {
        Serial.println("QuadRelays Write: Invalid  value");
        return invalidParams;
    }
    for(int i=0; i<num_bits;i++)
    {
        Serial.println(value & (1<<i));
        if(value & (1<<i))
        {
            digitalWrite(relayPin+i, true);
        }
        else
        {
            digitalWrite(relayPin+i, false);
        }
    }
    return (Tristate)true;
}


Tristate SoftataDevice_QuadRelays::SetBitState(bool state,int bitNo)
{
    Serial.println(bitNo);
    Serial.println(relayPin);
    Serial.println(num_bits);
    if(bitNo >= num_bits)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    else if(bitNo<0)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    Serial.println("Setting relay bit");
    Serial.print(bitNo);
    Serial.print(" to ");
    Serial.println(state);
    digitalWrite(relayPin+bitNo, state);
    return invalidParams;
}

Tristate SoftataDevice_QuadRelays::SetBit(int bitNo )
{
    Serial.println(bitNo);
    Serial.println(relayPin);
    Serial.println(num_bits);
    if(bitNo >= num_bits)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    else if(bitNo<0)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    Serial.print("Setting quadrelays bit: ");
    Serial.println(bitNo);
    digitalWrite(relayPin+bitNo, true);
    return (Tristate)true;
}

Tristate SoftataDevice_QuadRelays::ClearBit(int bitNo)
{
    Serial.println(bitNo);
    Serial.println(relayPin);
    Serial.println(num_bits);
    if(bitNo >= num_bits)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    else if(bitNo<0)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    Serial.print("Clearing quadrelays bit: ");
    Serial.println(bitNo);
    digitalWrite(relayPin+bitNo, false);
    return (Tristate)true;
}

Tristate SoftataDevice_QuadRelays::ToggleBit(int bitNo)
{
    Serial.println(bitNo);
    Serial.println(relayPin);
    Serial.println(num_bits);
    if(bitNo >= num_bits)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    else if(bitNo<0)
    {
        Serial.println("Setting quadrelays bit: Invalid bit number");
        return invalidParams;
    }
    Serial.print("Toggling quadrelays bit: ");
    Serial.println(bitNo);
    bool state = digitalRead(relayPin+bitNo);
    digitalWrite(relayPin+bitNo, !state);
    return (Tristate)true;
}