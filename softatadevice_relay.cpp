#include <Arduino.h>
#include "SoftataDevice_actuator.h"

SoftataDevice_Relay::SoftataDevice_Relay()
{
   
}

SoftataDevice_Relay::SoftataDevice_Relay(int pin)
{
    byte _relayPin = pin;
    Setup(&_relayPin,1);
}


bool SoftataDevice_Relay::Setup()
{
  byte _relayPin = 16;
  Setup(&_relayPin,1);
  return true;
}

bool SoftataDevice_Relay::Setup(byte * settings, byte numSettings)
{

  if(numSettings>0)
  {
    relayPin = settings[0];
  }
   else
   {
        Serial.print("Setting up Relay FAILED: No settings (pin no.)");
        return false;
   }
    Serial.print("Setting up relay on pin: ");
    Serial.println(relayPin);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, false);
    return true;
}

int SoftataDevice_Relay::GetNumBits()
{
    Serial.println("SoftataDevice_Relay::GetNumBits()");
    return num_bits;
}

int SoftataDevice_Relay::GetInstanceValueRange()
{
    return RELAY_MAX;
}

actuatorcapabilities SoftataDevice_Relay::GetActuatorCapabilities()
{
    return a_singlebit;
}

/*String SoftataDevice_Relay::GetPins()
{
    String msg = "Relay Pins";
    msg.concat(RELAY_PINOUT);
    return msg;
}*/

// Index for if there are an array of actuators here.
// Instance of is collected elsewhere.
// No longer need. 2Do Remove

Tristate SoftataDevice_Relay::Write(double value, int index)
{
    return notImplemented;
}

Tristate SoftataDevice_Relay::Write(int value, int index, int numBytes )
{
    return notImplemented;
}


Tristate SoftataDevice_Relay::SetBitState(bool state,int bitNo)
{
    Serial.println("Setting relay state");
    digitalWrite(relayPin, state);
    return (Tristate)true;
}

Tristate SoftataDevice_Relay::SetBit(int bitNo )
{
    Serial.println("Setting relay");
    digitalWrite(relayPin, true);
    return (Tristate)true;
}

Tristate SoftataDevice_Relay::ClearBit(int bitNo)
{
    Serial.println("Clearing relay");
    digitalWrite(relayPin, false);
    return (Tristate)true;
}

Tristate SoftataDevice_Relay::ToggleBit(int bitNo)
{
    Serial.println("Toggling relay");
    bool state = digitalRead(relayPin);
    digitalWrite(relayPin, !state);
    return (Tristate)true;
}