#include <Arduino.h>
#include "SoftataDevice_deviceinput.h"

SoftataDevice_GSwitch::SoftataDevice_GSwitch()
{
   
}

SoftataDevice_GSwitch::SoftataDevice_GSwitch(int pin)
{
    byte _gswitchPin = pin;
    Setup(&_gswitchPin,1);
}


bool SoftataDevice_GSwitch::Setup()
{
  byte _gswitchPin = 16;
  Setup(&_gswitchPin,1);
  return true;
}

bool SoftataDevice_GSwitch::Setup(byte * settings, byte numSettings)
{

  if(numSettings>0)
  {
    gswitchPin = settings[0];
  }
   else
   {
        Serial.print("Setting up Relay FAILED: No settings (pin no.)");
        return false;
   }
    Serial.print("Setting up relay on pin: ");
    Serial.println(gswitchPin);
    pinMode(gswitchPin, INPUT);
    digitalWrite(gswitchPin, false);
    return true;
}

int SoftataDevice_GSwitch::GetNumBits()
{
    Serial.println("SoftataDevice_GSwitch::GetNumBits()");
    return num_bits;
}

int SoftataDevice_GSwitch::GetInstanceValueRange()
{
    return GSWITCH_MAX;
}

byte SoftataDevice_GSwitch::GetInputCapabilities()
{
    return (byte)(i_none);
}

/*String SoftataDevice_GSwitch::GetPins()
{
    String msg = "Relay Pins";
    msg.concat(RELAY_PINOUT);
    return msg;
}*/

// Index for if there are an array of actuators here.
// Instance of is collected elsewhere.
// No longer need. 2Do Remove


word SoftataDevice_GSwitch::readWord()
{
    return 0xffff;
}

byte SoftataDevice_GSwitch::readByte()
{
    return 0xff;
}


bool SoftataDevice_GSwitch::PollBit(byte bitNo)
{
    Serial.println("Getting gswitch");
    return digitalRead(gswitchPin);
}

