
#include "SoftataDevice_environsensors.h"

      
SoftataDevice_Sensor *  _GetNewSensorInstance(byte deviceInstanceType)
{
    SoftataDevice_Sensor * dev = NULL;
    switch (deviceInstanceType)

    {
        case DHT11:
            dev  = new SoftataDevice_DHT11(16);
            break;
        case DHTXX:
            //dev  = new SoftataDevice_DHTXX();
            break;
        case BME280:
            dev  = new SoftataDevice_BME280();
            break;
        case UltrasonicRanger:
            dev  = new SoftataDevice_URangeSensor(DEFAULT_URANGE_PIN);
            break;
        case Simulator:
            dev  = new SoftataDevice_SensorSimulator();
            break;
        ///////////////////////////
        // Add more sensors here // 
        ///////////////////////////
        default:
            dev = NULL;
            break;
    }
    return dev;
}

SoftataDevice_Sensor * SoftataDevice_Sensor::_Getup(byte _sensor)
{
    SoftataDevice_Sensor * dev = _GetNewSensorInstance(_sensor);
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

SoftataDevice_Sensor * SoftataDevice_Sensor::_Getup(byte actuator, byte * settings, byte numSettings)
{
    SoftataDevice_Sensor * dev = _GetNewSensorInstance(actuator);
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

      static String _GetListofCmds()
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

      String SoftataDevice_Sensor::_GetListofProperties(byte sen)
      {
        String props ="";
        switch (sen)
        {
          //#define SENSORS C(DHT11)C(SWITCH)C(SOUND)C(BME280)
          case DHT11:
            {
              props = SoftataDevice_DHT11::GetListofProperties();
            }
            break;
            case DHTXX:
            {
              //props = SoftataDevice_DHTXX::GetListofProperties();
            }
            break;                       
          case BME280:
            {
              props = SoftataDevice_BME280::GetListofProperties();
            }
            break;
          case UltrasonicRanger:
            {
              props = SoftataDevice_URangeSensor::GetListofProperties();
            }
            break; 
          case Simulator:
            {
              props = SoftataDevice_SensorSimulator::GetListofProperties();
            } 
            break;                     
          // Add more here
          default:
            {
              props = "Fail:Not a sensor-Get Properties:";
              props += sen;
            }
            break;
        }
        return props;
      }