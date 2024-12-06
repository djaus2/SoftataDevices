
#include "SoftataDevice_display.h"

      
SoftataDevice_Display *  GetNewDisplayInstance(byte deviceInstanceType)
{
    SoftataDevice_Display * dev = NULL;
    switch (deviceInstanceType)
    {
        case OLED096:
            dev  = new SoftataDevice_OLED096();
            break;
        case LCD1602:
            dev  = new SoftataDevice_LCD1602();
            break;
        case NEOPIXEL:
            dev  = new Adafruit_NeoPixel8();
            break;
        case BARGRAPH:
            dev  = new Custom_Bargraph();
            break;
        case GBARGRAPH:
            dev  = new SoftataDevice_Bargraph();
            break;                       
        ////////////////////////////
        // Add more displays here // 
        ////////////////////////////
        default:
            dev = NULL; 
            break;  
    }
    return dev;
}

SoftataDevice_Display * SoftataDevice_Display::GSetup(byte _display)
{
    SoftataDevice_Display * dev = GetNewDisplayInstance(_display);
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

SoftataDevice_Display * SoftataDevice_Display::GSetup(byte _display, byte * settings, byte numSettings)
{
    SoftataDevice_Display * dev = GetNewDisplayInstance(_display);
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