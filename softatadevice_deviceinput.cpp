
#include "SoftataDevice_DeviceInput.h"

      
SoftataDevice_DeviceInput *  GetNewInputnstance(byte deviceInstanceType)
{
    SoftataDevice_DeviceInput * dev = NULL;
    switch (deviceInstanceType)
    {
        case GSWITCH:
            dev  = new SoftataDevice_GSwitch();
            break;
        case PISO74HC165:
            dev  = new Piso74HC165();
            break;
        /////////////////////////////
        // Add more inputs here // 
        /////////////////////////////
        default:
            dev = NULL; 
            break;  
    }
    return dev;
}



SoftataDevice_DeviceInput * SoftataDevice_DeviceInput::_Setup(byte _input)
{
    SoftataDevice_DeviceInput * dev = GetNewInputnstance(_input);
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

SoftataDevice_DeviceInput * SoftataDevice_DeviceInput::_Setup(byte _input, byte * settings, byte numSettings)
{
    SoftataDevice_DeviceInput * dev = GetNewInputnstance(_input);
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