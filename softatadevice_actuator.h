#ifndef SoftataDevice_ACTUATORH
#define SoftataDevice_ACTUATORH
#include "softatadevice.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


#define C(x) #x,
const char * const ACTUATOR_CMDS[] = { ACTUATOR_COMMANDS  };
#undef C

#define C(x) x,
enum SoftataActuatorCmds { ACTUATOR_COMMANDS ACTUATOR_COMMANDS_NONE };
#undef C



#define C(x) x,
enum SoftataActuator { ACTUATORS ACTUATOR_NONE};
#undef C
#define C(x) #x,    
const char * const actuator_name[] = { ACTUATORS  };
#undef C



class SoftataDevice_Actuator: public SoftataDevice
{
    public:


      static SoftataDevice_Actuator * _Setup(byte actuator);
      static SoftataDevice_Actuator * _Setup(byte actuator, byte * settings, byte numSettings);

      static String GetListofDevices()
      {
        String list ="ACTUATORS:";
        int numActuators = (int) ACTUATOR_NONE;
        for (int n=0;n<numActuators;n++)
        {
          list.concat(actuator_name[n]);
          if (n != (numActuators-1))
            list.concat(',');
        }
        return list;
      }

      static arduino::String  GetRange(byte act)
      {
          String msg = "Actuator Range:";
          msg.concat(ACTUATOR_RANGES[act]);
          return msg;
      }

      static String GetListofCmds()
      {
        String list ="Actuator Cmds:";
        int numCMDS = (int) ACTUATOR_COMMANDS_NONE;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(ACTUATOR_CMDS[n]);
          //cmd.replace("a_","");
          //cmd.replace("A_","");
          //cmd.replace("A__","");
          cmd.replace("CMD","");
          cmd.replace("cmd","");
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      static int GetIndexOf(String actuatorName)
      {
        int numActuators = (int) ACTUATOR_NONE;
        for (int n=0;n<numActuators;n++)
        {
          SoftataActuator s = (SoftataActuator)n;
          String name = String(actuator_name[s]);
          if (actuatorName.compareTo(name)==0)
          {
            return (int)s;
          }
        }
        return INT_MAX;
      }   
 


      virtual String GetListofx()
      {
        return SoftataDevice_Actuator::GetListofDevices();
      }

      static String GetName(byte sen)
      {
        return String(actuator_name[sen]);
      }

      static String GetPinout(byte sen)
      {
        Serial.print("Actuator index:");
        Serial.println(sen);
        Serial.print("Actuator name:");
        Serial.println(actuator_name[sen]);
        Serial.print("Actuator pinout:");
        Serial.println(ACTUATOR_PINOUTS[sen]);
        return String(ACTUATOR_PINOUTS[sen]);
      }

  
      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      static String GetValueRange();
      static String GetPins();

      virtual int GetNumBits();
      virtual int GetInstanceValueRange();

      // Index for if there are an array of actuators here.
      virtual Tristate Write(double value, int index);
      virtual Tristate Write(int value, int index, int numBytes = 1);
      virtual Tristate SetBitState(bool state,int index);
      virtual Tristate SetBit(int index = 0);
      virtual Tristate ClearBit(int index = 0);
      virtual Tristate ToggleBit(int index = 0);
      DeviceType deviceType = actuator;
    protected:
      int num_properties=0;
      int num_bits = 0;
      // Use following to indicate an error
};
#endif

#ifndef RELAYH
#define RELAYH


class SoftataDevice_Relay: public SoftataDevice_Actuator
{
    public:
      SoftataDevice_Relay();
      SoftataDevice_Relay(int pin);

      static arduino::String GetValueRange()
      {
        String msg = "Relay Rangge: ";
        msg.concat(RELAY_RANGE);
        return msg;
      }

      static arduino::String  GetPins()
      {
          String msg = "Relay Pins: ";
          msg.concat(RELAY_PINOUT);
          return msg;
      }



      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      //virtual String GetPins();

      virtual int GetNumBits();
      virtual int GetInstanceValueRange();
  
      // Index for if there are an array of actuators here.
      virtual Tristate Write(double value, int index);
      virtual Tristate Write(int value, int index, int numBytes = 1);
      virtual Tristate SetBitState(bool state,int index);
      virtual Tristate SetBit(int index );
      virtual Tristate ClearBit(int index );
      virtual Tristate ToggleBit(int index );
      DeviceType deviceType = actuator;
    protected:
      int num_properties=0;
      int num_bits = 1;
      byte relayPin = 16;
};
#endif

#ifndef QUADRELAYH
#define QUADRELAYH


class SoftataDevice_QuadRelays: public SoftataDevice_Actuator
{
    public:
      SoftataDevice_QuadRelays();
      SoftataDevice_QuadRelays(int pin);

      static arduino::String GetValueRange()
      {
        String msg = "QuadRelays Range: 0...";
        int _maxrange =  pow(2,DEFAULT_QUADRELAYS_NUM_BITS)-1;
        msg.concat(_maxrange);
        return msg;
      }

      static arduino::String  GetPins()
      {
          String msg = "QuadRelays Pins: ";
          msg.concat(QUADRELAYS_PINOUT);
          return msg;
      }

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      //virtual String GetPins();

     virtual int GetNumBits();
     virtual int GetInstanceValueRange();

      // Index for if there are an array of actuators here.
      virtual Tristate Write(double value, int index);
      virtual Tristate Write(int value, int index, int numBytes = 1);
      virtual Tristate SetBitState(bool state,int index);
      virtual Tristate SetBit(int index );
      virtual Tristate ClearBit(int index );
      virtual Tristate ToggleBit(int index );
      DeviceType deviceType = actuator;
    protected:
      int num_properties=1;
      int num_bits = DEFAULT_QUADRELAYS_NUM_BITS;

      byte relayPin = 16;
};
#endif

#ifndef SERVOH
#define SERVOH

#include <Servo.h>

#define MAX_PW 2400
#define MIN_PW 544
#define PERIOD 20000


class SoftataDevice_Servo: public SoftataDevice_Actuator
{
    public:
      SoftataDevice_Servo();
      SoftataDevice_Servo(int pin);

      static arduino::String GetValueRange()
      {
        String msg = "";;
        msg.concat(SERVO_RANGE);
        return msg;
      }

      static arduino::String GetPins()
      {
          String msg = "Servo Pins:";
          msg.concat(SERVO_PINOUT);
          return msg;
      }

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      //virtual String GetPins();

      virtual int GetNumBits();
      virtual int GetInstanceValueRange();

      // Index for if there are an array of actuators here.
      virtual Tristate Write(double value, int index);
      virtual Tristate Write(int value, int index, int numBytes = 1);
      virtual Tristate SetBitState(bool state,int index);
      virtual Tristate SetBit(int index );
      virtual Tristate ClearBit(int index );
      virtual Tristate ToggleBit(int index );
      DeviceType deviceType = actuator;
    protected:
      virtual bool SetupServo(int pin, int min, int max, int period);
      int num_properties=0;
      int num_bits = -1;
      Servo myservo;
};
#endif

#ifndef SIPO_74HC595H
#define SIPO_74HC595H

#include "ic_74hc595_shiftRegister.h"

#define NUM_SETTINGS 4 // 3 pins plus number of bytes

class Sipo74hc95: public SoftataDevice_Actuator
{
    public:
      Sipo74hc95();
      Sipo74hc95(byte * settings);

      static arduino::String GetValueRange()
      {
        String msg = "";;
        msg.concat(SIPO_74HC595_RANGE);
        return msg;
      }

      static arduino::String  GetPins()
      {
          String msg = "SIPO_74HC595 Pins:";
          msg.concat(SIPO_74HC595_PINOUT);
          return msg;
      }


      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      //virtual String GetPins();

     virtual int GetNumBits();
     virtual int GetInstanceValueRange();     

      // Index for if there are an array of actuators here.
      virtual Tristate Write(double value, int index);
      virtual Tristate Write(int value, int index, int numBytes = 1);
      virtual Tristate SetBitState(bool state,int bitNo);
      virtual Tristate SetBit(int bitNo );
      virtual Tristate ClearBit(int bitNo );
      virtual Tristate ToggleBit(int bitNo );
      DeviceType deviceType = actuator;
    protected:
      int num_settings=NUM_SETTINGS;
      int num_bytes=1;
      int num_bits = -1;
      IC_74HC595_ShiftRegister * ic595;
};
#endif


