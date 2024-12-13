#ifndef SoftataDevice_SENSORH
#define SoftataDevice_SENSORH
#include <Arduino.h>
#include "softatadevice.h"
#include "SoftataDeviceInfo.h"

#define NUM_PROPERTIES 0

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


#define C(x) #x,
const char * const SENSOR_CMDS[] = { SENSOR_COMMANDS  };
#undef C

#define C(x) x,
enum SoftataSensorCmds { SENSOR_COMMANDS SENSOR_COMMANDS_NONE };
#undef C



#define C(x) x,
enum SoftataSensor { SENSORS SENSOR_NONE};
#undef C

#define C(x) #x,    
const char * const sensor_name[] = { SENSORS };
#undef C

class SoftataDevice_Sensor: public SoftataDevice
{
    public:

      static SoftataDevice_Sensor * _Setup(byte display);
      static SoftataDevice_Sensor * _Setup(byte display, byte * settings, byte numSettings);   
      static String _GetListofProperties(byte sen);

      static String GetListofProperties(byte sen)
      {
        return String(SENSOR_PROPERTIES[sen]);
      }

      static String GetListofDevices()
      {
        String list ="SENSORS:";
        int numSensors = (int) SENSOR_NONE;
        for (int n=0;n<numSensors;n++)
        {
          list.concat(sensor_name[n]);
          if (n != (numSensors-1))
            list.concat(',');
        };
        return list;
      }

      static String GetListofCmds()
      {
        String list ="Sensor Cmds:";
        int numCMDS = (int) SENSOR_COMMANDS_NONE;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(SENSOR_CMDS[n]);
          cmd.replace("s_","");
          cmd.replace("S_","");
          cmd.replace("CMD","");
          cmd.replace("cmd","");
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }


      static String GetName(byte sen)
      {
        return String(sensor_name[sen]);
      }

      static String GetPinout(byte sen)
      {
        return String(SENSOR_PINOUTS[sen]);
      }

      static int GetIndexOf(String sensorName)
      {
        int numSensors = (int) SENSOR_NONE;
        for (int n=0;n<numSensors;n++)
        {
          SoftataSensor s = (SoftataSensor)n;
          String name = String(sensor_name[s]);
          if (sensorName.compareTo(name)==0)
          {
            return (int)s;
          }
        }
        return INT_MAX;
      }

      static String GetListofx()
      {
        return SoftataDevice_Sensor::GetListofDevices();
      }

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings=1);
      static String GetPins();

      virtual bool ReadAll(double * values);
      virtual String GetTelemetry();
      virtual double Read(int property);
      virtual CallbackInfo * GetCallbackInfo();
      DeviceType deviceType = sensor;
      SoftataSensor sensorType = SENSOR_NONE;
      int num_properties;
    protected:
      

};
#endif
