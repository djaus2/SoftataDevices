
#include "SoftataDevice_display.h"

      
SoftataDevice_Display *  SoftataDevice_Display::_GetNewDisplayInstance(byte displayType)
{
    SoftataDevice_Display * dev = NULL;
    switch (displayType)
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
    if(dev != nullptr)
    {
        dev->DisplayType = (SoftataDisplay)displayType;
    }
    return dev;
}

String SoftataDevice_Display::_GetListofMiscCmds(byte displayType)
{
    const char* const* miscCmds = NULL;
    int max = 0;

    switch (displayType)
    {
        case OLED096:
            miscCmds  = OLEDMiscCmdsArr;
            max = OLEDMiscCmds_MAX;
            break;
        case LCD1602:
            miscCmds  = LCD1602MiscCmdsArr;
            max = LCD1602MiscCmds_MAX;
            break;
        case NEOPIXEL:
            miscCmds  = NEOPIXELMiscCmdsArr;
            max = NEOPIXELMiscCmds_MAX;
            break;
        case BARGRAPH:
            miscCmds  = BARGRAPHMiscCmdsArr;
            max = BARGRAPHMiscCmds_MAX;
        case GBARGRAPH:
            miscCmds  = CUSTOM_BARGRAPHMiscCmdsArr;
            max = _BARGRAPHMiscCmds_MAX;
            break;                       
        ////////////////////////////
        // Add more displays here // 
        ////////////////////////////
        default:
            miscCmds = NULL;
            max = 0;
            break;  
    }
    if ((max > 0) && (miscCmds != NULL))
    {
        String list ="DISPLAY MISC CMDS:";
        for (int n=0;n<max;n++)
        {
            list.concat(String(miscCmds[n]));
            if (n != (max-1))
            list.concat(',');
        }
        return list;
    }
    else
    {
        return "Error: No display found";
    }
}

SoftataDevice_Display * SoftataDevice_Display::_Setup(byte displayType)
{
    SoftataDevice_Display * dev = _GetNewDisplayInstance(displayType);
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

SoftataDevice_Display * SoftataDevice_Display::_Setup(byte displayType, byte * settings, byte numSettings)
{
    SoftataDevice_Display * dev = _GetNewDisplayInstance(displayType);
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