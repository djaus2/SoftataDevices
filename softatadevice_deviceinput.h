#ifndef SoftataDevice_DEVICEINPUTH
#define SoftataDevice_DEVICEINPUTH
#include "softatadevice.h"

#include "ic_74hc165_shiftRegister.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


#define C(x) #x,
const char * const DEVICEINPUT_CMDS[] = { DEVICEINPUT_COMMANDS  };
#undef C

#define C(x) x,
enum SoftataDeviceInputCmds { DEVICEINPUT_COMMANDS DEVICEINPUT_COMMANDS_NONE };
#undef C



#define C(x) x,
enum SoftataDeviceInput { DEVICEINPUTS DEVICEINPUT_NONE};
#undef C
#define C(x) #x,    
const char * const deviceinput_name[] = { DEVICEINPUTS };
#undef C



class SoftataDevice_DeviceInput: public SoftataDevice
{
    public:


      static SoftataDevice_DeviceInput * _Setup(byte deviceinput);
      static SoftataDevice_DeviceInput * _Setup(byte deviceinput, byte * settings, byte numSettings);

      static String GetListofDevices()
      {
        String list ="DEVICEINPUTS:";
        int numInputs= (int) DEVICEINPUT_NONE;
        for (int n=0;n<numInputs;n++)
        {
          list.concat(deviceinput_name[n]);
          if (n != (numInputs-1))
            list.concat(',');
        }
        return list;
      }

      static arduino::String  GetRange(byte inpt)
      {
          String msg = "Input Range:";
          msg.concat(DEVICEINPUT_RANGES[inpt]);
          return msg;
      }

      static String GetListofCmds()
      {
        String list ="DeviceInput Cmds:";
        int numCMDS = (int) DEVICEINPUT_COMMANDS_NONE;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(DEVICEINPUT_CMDS[n]);
          //cmd.replace("i_","");
          //cmd.replace("I_","");
          //cmd.replace("I__","");
          cmd.replace("CMD","");
          cmd.replace("cmd","");
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      static int GetIndexOf(String deviceinputName)
      {
        int numInputs = (int) DEVICEINPUT_NONE;
        for (int n=0;n<numInputs;n++)
        {
          //SoftataDevice_DeviceInput i = (SoftataDevice_DeviceInput)n;
          String name = String(deviceinput_name[n]);
          if (deviceinputName.compareTo(name)==0)
          {
            return (int)n;
          }
        }
        return INT_MAX;
      }   
 


      virtual String GetListofx()
      {
        return SoftataDevice_DeviceInput::GetListofDevices();
      }

      static String GetName(byte inpt)
      {
        return String(deviceinput_name[inpt]);
      }

      static String GetPinout(byte inpt)
      {
        Serial.print("DeviceInput index:");
        Serial.println(inpt);
        Serial.print("DeviceInput name:");
        Serial.println(deviceinput_name[inpt]);
        Serial.print("Input pinout:");
        Serial.println(DEVICEINPUT_PINOUTS[inpt]);
        return String(DEVICEINPUT_PINOUTS[inpt]);
      }

  
      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);

      virtual byte GetInputCapabilities();
      static String GetValueRange();
      static String GetPins();

      virtual int GetNumBits();
      virtual int GetInstanceValueRange();

      // Index for if there are an array of deviceinputs here.
      virtual byte readByte();
      virtual word readWord();
      virtual bool PollBit(byte bitNo=0);
      DeviceType deviceType = deviceinput;
    protected:
      int num_properties=0;
      int num_bits = 0;
      // Use following to indicate an error
};
#endif

#ifndef GSWITCHH
#define GSWITCHH


class SoftataDevice_GSwitch: public SoftataDevice_DeviceInput
{
    public:
      SoftataDevice_GSwitch();
      SoftataDevice_GSwitch(int pin);

      static arduino::String GetValueRange()
      {
        String msg = "GSwitch Range: ";
        msg.concat(GSWITCH_RANGE);
        return msg;
      }

      static arduino::String  GetPins()
      {
          String msg = "GSwitch Pins: ";
          msg.concat(GSWITCH_PINOUT);
          return msg;
      }

      virtual byte GetInputCapabilities();

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);

      virtual int GetNumBits();
      virtual int GetInstanceValueRange();

      // Index for if there are an array of deviceinputs here.
      virtual byte readByte();
      virtual word readWord();
      virtual bool PollBit(byte bitNo=0);

      DeviceType deviceType = deviceinput;
    protected:
      int num_properties=0;
      int num_bits = 1;
      byte gswitchPin = 16;
};
#endif

#ifndef SIPINH
#define SIPINH



#define NUM_SETTINGS 4 // 3 pins plus number of bytes

class Piso74HC165: public SoftataDevice_DeviceInput
{
    public:
      Piso74HC165();
      Piso74HC165(int pin);

      static arduino::String GetValueRange()
      {
        String msg = "PISO74HC165 Range: ";
        msg.concat(PISO74HC165_RANGE);
        return msg;
      }

      static arduino::String  GetPins()
      {
          String msg = "PISO74HC165 Pins: ";
          msg.concat(PISO74HC165_PINOUT);
          return msg;
      }

      virtual byte GetInputCapabilities();

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);

      virtual int GetNumBits();
      virtual int GetInstanceValueRange();

      // Index for if there are an array of deviceinputs here.
      virtual byte readByte();
      virtual word readWord();
      virtual bool PollBit(byte bitNo=0);

      DeviceType deviceType = deviceinput;
    protected:
      int num_settings=NUM_SETTINGS;
      int num_bytes= DEFAULT_PISO74HC165_NUM_BYTES;
      int num_bits = -1;
      int pin = DEFAULT_PISO74HC165_PIN;
      IC_74HC165_ShiftRegister * ic165;
};
#endif


