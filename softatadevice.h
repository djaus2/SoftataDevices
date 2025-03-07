#ifndef GROVEH
#define GROVEH
#include "SoftataDeviceInfo.h"
#include <wString.h>
#include <Wire.h>

// As per softata.h:
//enum DeviceType  {sensor,actuator,communication,display};
#define DEVICETYPES  G_DEVICETYPES
#define SENSORS      G_SENSORS
#define ACTUATORS    G_ACTUATORS
#define DISPLAYS     G_DISPLAYS
#define DEVICEINPUTS G_DEVICEINPUTS

#define C(x) x,
enum DeviceType { DEVICETYPES DEVICETYPE_NONE};
#undef C
#define C(x) #x,    
const char * const device_name[] = { DEVICETYPES };
#undef C

class SoftataDevice
{
    public:

      SoftataDevice()
      {
        
      }

      static byte GetSoftataDeviceCmdBase()
      {
        return SOFTATDEVICE_CMD;
      }

/*
      static SoftataDevice(SoftataDevice_Actutor * act)
      {
        deviceType = actuator;
      }

      static SoftataDevice(SoftataDevice_Sensor * sens)
      {
        deviceType = sensor;
      }


      static SoftataDevice(SoftataDevice_Display * disp)
      {
        deviceType = display;
      } */

     static String GetListofCmds();
     static String GetNamet(byte device);
     static String GetPinout(byte device);


    //To be called before Wire.begin()/Wire1.begin()
    static bool SetI2CPins(int i2c)
    {
      if (i2c==0)
      {
        Wire.setSDA(I2C0_SDA);
        Wire.setSCL(I2C0_SCL);
        return true;
      }
      else if (i2c==1)
      {
#ifndef UNO
        Wire1.setSDA(I2C1_SDA);
        Wire1.setSCL(I2C1_SCL); 
        return true;    
#endif
        return false;
      }
      return false;
    }

    static String GetListofDevices()
    {
      String list ="DEVICES:";
      int numDevices = (int) DEVICETYPE_NONE;
      for (int n=0;n<numDevices;n++)
      {
        list.concat(device_name[n]);
        if (n != (numDevices-1))
          list.concat(',');
      }
      return list;
    }

    virtual bool Setup();
    virtual bool Setup(byte * settings, byte numSettings=1);
    DeviceType deviceType;
      
    protected:
      
      
};
#endif