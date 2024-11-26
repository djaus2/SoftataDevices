#include <Arduino.h>
#include "grove_actuator.h"

Grove_Servo::Grove_Servo()
{
    Setup();
}

Grove_Servo::Grove_Servo(int pin)
{
    SetupServo(pin,MIN_PW,MAX_PW,PERIOD);
}

bool Grove_Servo::Setup()
{
    return SetupServo(DEFAULT_SERVO_PIN,MIN_PW,MAX_PW,PERIOD);
}

bool Grove_Servo::Setup(byte * settings, byte numSettings)
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

/*
String Grove_Servo::GetPins()
{
    String msg = "OK:Servo Pins:";
    msg.concat(SERVO_PINOUT);
    return msg;
}*/

bool Grove_Servo::SetupServo(int pin, int min, int max, int period)
{
    myservo.attach(pin,min,max);
    return true;
}


// Index for if there are an array of actuators here.
bool Grove_Servo::Write(double value, int index)
{
    return true;
}

bool Grove_Servo::Write(int angle, int index, int numBytes /*=1*/)
{
    if((index<0)||(index>180))
        return false;
    myservo.write(angle);
    return true;
}

bool Grove_Servo::SetBitState(bool state,int bitIndex)
{
    return true;
}

bool Grove_Servo::SetBit(int bitNo )
{
    return true;
}

bool Grove_Servo::ClearBit(int bitNo)
{
    return true;
}

bool Grove_Servo::ToggleBit(int bitNo)
{
    return true;
}