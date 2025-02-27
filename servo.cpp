#include <Arduino.h>
#include "SoftataDevice_actuator.h"

SoftataDevice_Servo::SoftataDevice_Servo()
{
    Setup();
}

SoftataDevice_Servo::SoftataDevice_Servo(int pin)
{
    SetupServo(pin,MIN_PW,MAX_PW,PERIOD);
}

bool SoftataDevice_Servo::Setup()
{
    return SetupServo(DEFAULT_SERVO_PIN,MIN_PW,MAX_PW,PERIOD);
}

bool SoftataDevice_Servo::Setup(byte * settings, byte numSettings)
{
    if(numSettings>0)
    {
        int pin = settings[0];
        if(numSettings>1)
        {
            int min = settings[1];
            if(numSettings>2)
            {
                int max = settings[2];
                if(numSettings>3)
                {
                    int period = settings[3];
                    return SetupServo(pin,min,max,period);
                }
                else
                    return SetupServo(pin,min,max,PERIOD);
            }
            else
                return SetupServo(pin,min,MAX_PW,PERIOD);
        }
        else
            return SetupServo(pin,MIN_PW,MAX_PW,PERIOD);
    }
    else
        return SetupServo(DEFAULT_SERVO_PIN,MIN_PW,MAX_PW,PERIOD);
}

int SoftataDevice_Servo::GetNumBits()
{
    Serial.print("SoftataDevice_Servo::GetNumBits():");
    Serial.println(num_bits);
    return num_bits;
}

int SoftataDevice_Servo::GetInstanceValueRange()
{
    return SERVO_MAX;
}

byte SoftataDevice_Servo::GetActuatorCapabilities()
{
    return (byte)(a_writebyte);
}

/*
String SoftataDevice_Servo::GetPins()
{
    String msg = "Servo Pins:";
    msg.concat(SERVO_PINOUT);
    return msg;
}*/

bool SoftataDevice_Servo::SetupServo(int pin, int min, int max, int period)
{
    myservo.attach(pin,min,max);
    return true;
}


// Index for if there are an array of actuators here.
Tristate SoftataDevice_Servo::Write(double value, int index)
{
    return notImplemented;
}

Tristate SoftataDevice_Servo::Write(int angle, int index, int numBytes /*=1*/)
{
    if((angle<SERVO_MIN)||(angle>SERVO_MAX))
        return invalidParams;
    myservo.write(angle);
    return (Tristate)true;
}

Tristate SoftataDevice_Servo::SetBitState(bool state,int bitIndex)
{
    return notImplemented;
}

Tristate SoftataDevice_Servo::SetBit(int bitNo )
{
    return notImplemented;
}

Tristate SoftataDevice_Servo::ClearBit(int bitNo)
{
    return notImplemented;
}

Tristate SoftataDevice_Servo::ToggleBit(int bitNo)
{
    return notImplemented;
}