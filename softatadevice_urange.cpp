#include "SoftataDevice_environsensors.h"
#include <arduino.h>
#include "Ultrasonic.h"

#include <float.h>
#include "SoftataDeviceInfo.h"

Ultrasonic * ultrasonic;

SoftataDevice_URangeSensor::SoftataDevice_URangeSensor(int SetupPin)
{
    ultrasonic = new Ultrasonic(SetupPin);
    SoftataDevice_Sensor::num_properties = NUM_URANGE_PROPERTIES;
    SoftataDevice_Sensor::sensorType = UltrasonicRanger;
}

bool SoftataDevice_URangeSensor::Setup(byte * settings, byte numSettings)
{
    return true;
}

bool SoftataDevice_URangeSensor::Setup()
{
    return true;
}

String SoftataDevice_URangeSensor::GetPins()
{
    String msg = "Ultrasonic Range Sensor Pins:";
    msg.concat(URANGE_PINOUT);
    return msg;
}

CallbackInfo * SoftataDevice_URangeSensor::GetCallbackInfo()
{
    info.period = 314159;
    info.next = 137;
    info.SensorIndex = 123456;
    info.sendBT = false;
    info.isSensor=false;
    info.isRunning=false;
    return &info;
}


bool SoftataDevice_URangeSensor::ReadAll(double* values)
{
    values[0] = (double)ultrasonic->MeasureInMillimeters();
    if(values[0]==0)
        values[0] = (double)ultrasonic->MeasureInMillimeters();
    values[1] = (double)ultrasonic->MeasureInCentimeters();
    if(values[1]==0)
        values[1] = (double)ultrasonic->MeasureInCentimeters();
    values[2] = (double)ultrasonic->MeasureInInches();
    if(values[2]==0)
        values[2] = (double)ultrasonic->MeasureInInches();
    return true;
}

String SoftataDevice_URangeSensor::GetTelemetry()
{
    double values[3];
    if(ReadAll(values))
    {
        String msg ="{\"MeasureInMillimeters\":";
        msg.concat(values[0]);
        msg.concat(',');
        msg.concat("\"MeasureInCentimeters\":");
        msg.concat(values[1]);
        msg.concat(',');
        msg.concat("\"MeasureInInches\":");
        msg.concat(values[2]);
        msg.concat('}');
        return msg;
    }
    else
        return "ERRORDBL";
}

double SoftataDevice_URangeSensor::Read(int property)
{
    if(property==0)
    {
        return (double)ultrasonic->MeasureInMillimeters();
    }
    else if(property==1)
    {
        return (double)ultrasonic->MeasureInCentimeters();
    }
    else if(property==2)
    {
        return (double)ultrasonic->MeasureInInches();
    }
    else
        return DBL_MAX;
}