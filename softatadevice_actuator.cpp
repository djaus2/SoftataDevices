
#include "SoftataDevice_actuator.h"

      
SoftataDevice_Actuator *  GetNewActuatorInstance(byte deviceInstanceType)
{
    SoftataDevice_Actuator * dev = NULL;
    switch (deviceInstanceType)
    {
        case SERVO:
            dev  = new SoftataDevice_Servo();
            break;
        case SIPO_74HC595:
            dev  = new Sipo74hc95();
            break;
        case RELAY:
            dev  = new SoftataDevice_Relay();
            break;
        case QUADRELAYS:
            dev  = new SoftataDevice_QuadRelays();
            break;
        /////////////////////////////
        // Add more actuators here // 
        /////////////////////////////
        default:
            dev = NULL; 
            break;  
    }
    return dev;
}



SoftataDevice_Actuator * SoftataDevice_Actuator::_Setup(byte _actuator)
{
    SoftataDevice_Actuator * dev = GetNewActuatorInstance(_actuator);
    if (dev == NULL)
        return NULL;
    if(dev->Setup())
    {
        return dev;
    }
    else
    {
        return NULL;
    }
}

SoftataDevice_Actuator * SoftataDevice_Actuator::_Setup(byte _actuator, byte * settings, byte numSettings)
{
    SoftataDevice_Actuator * dev = GetNewActuatorInstance(_actuator);
    if (dev == NULL)
        return NULL;
    if( dev->Setup(settings,numSettings))
    {
        return dev;
    }
    else
    {
        return NULL;
    }
}