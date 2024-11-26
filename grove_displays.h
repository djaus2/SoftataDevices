#ifndef GROVE_DISPLAYHI2CDISPLAYS
#define GROVE_DISPLAYHI2CDISPLAYS
#include "grove.h"



#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


#define C(x) #x,
const char * const CMDS[] = { DISPLAY_COMMANDS  };
#undef C

#define C(x) x,
enum GroveDisplayCmds { DISPLAY_COMMANDS DISPLAY_COMMANDS_NONE };
#undef C

////////////////////////////////////////////////////////

#define C(x) x,
enum GroveDisplay { DISPLAYS DISPLAY_NONE};
#undef C

#define C(x) #x,    
const char * const display_name[] = { DISPLAYS };
#undef C



class Grove_Display: public Grove
{
    public:




      static String GetListof()
      {
        String list ="Displays:";
        int numDISPLAYS = (int) DISPLAY_NONE;
        for (int n=0;n<numDISPLAYS;n++)
        {
          list.concat(display_name[n]);
          if (n != (numDISPLAYS-1))
            list.concat(',');
        }
        return list;
      }

      static String GetListofCmds()
      {
        String list ="Display Cmds:";
        int numCMDS = (int) DISPLAY_COMMANDS_NONE;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(CMDS[n]);
          cmd.replace("d_","");
          cmd.replace("D_","");
          cmd.replace("CMD","");
          cmd.replace("cmd","");
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      static String GetName(byte disp)
      {
        return String(display_name[disp]);
      }

      static String GetPinout(byte disp)
      {
        return String(DISPLAY_PINOUTS[disp]);
      }

      static int GetIndexOf(String displayName)
      {
        int numDisplays = (int) DISPLAY_NONE;
        for (int n=0;n<numDisplays;n++)
        {
          GroveDisplay s = (GroveDisplay)n;
          String name = String(display_name[s]);
          if (displayName.compareTo(name)==0)
          {
            return (int)s;
          }
        }
        return INT_MAX;
      }  

      virtual String GetListofx()
      {
        return Grove_Display::GetListof();
      }

  
      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      static String GetPins();
      static String GetListofMiscCmds();

      virtual Tristate Dummy();

      virtual Tristate Home();
      virtual Tristate Clear();
      virtual Tristate Backlight();
      virtual Tristate SetCursor(byte x, byte y);
      virtual Tristate WriteString(String msg);
      virtual Tristate CursorWriteStringAvailable();
      virtual Tristate WriteString(byte x, byte y, String msg);
      virtual Tristate Misc(byte cmd, byte * data, byte length=0);

      DeviceType deviceType = display;
    protected:
};
#endif

#ifndef OLED096H
#define OLED096H



class Grove_OLED096: public Grove_Display
{
  public:

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);

      static String GetPins()
      {
        String msg="OLED096 Display Pins:";
        msg.concat(OLED096_PINOUT);
        return msg;
      }

      static String GetListofMiscCmds()
      {
        String list ="OLED096 Display Misc  Cmds:";
        int numCMDS = (int) OLEDMiscCmds_MAX;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(OLEDMiscCmdsArr[n]);
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      virtual Tristate Dummy();
   
      virtual Tristate Home();
      virtual Tristate Clear();

      virtual Tristate Backlight();
      virtual Tristate SetCursor(byte x, byte y);
      virtual Tristate WriteString(String msg);
      // No cursor and or no writestring:
      virtual Tristate CursorWriteStringAvailable();
      virtual Tristate WriteString(byte col, byte line, String msg);
      virtual Tristate Misc(byte cmd, byte * data, byte length=0);
  protected:
};

#endif

#ifndef LCD1602H
#define LCD1602H



class Grove_LCD1602: public Grove_Display
{
  public:


      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      // Index for if there are an array of actuators here.

      static String GetPins()
      {
        String msg="OK:LCD1602 Display Pins:";
        msg.concat(LCD1602_PINOUT);
        return msg;
      }

      static String GetListofMiscCmds()
      {
        String list ="LCD1602 Display Misc  Cmds:";
        int numCMDS = (int) LCD1602MiscCmds_MAX;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(LCD1602MiscCmdsArr[n]);
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      virtual Tristate Dummy();

      virtual Tristate Home();
      virtual Tristate Clear();
      virtual Tristate Backlight();
      virtual Tristate SetCursor(byte x, byte y);
      virtual Tristate WriteString(String msg);
      // No cursor and or no writestring:
      virtual Tristate CursorWriteStringAvailable();
      virtual Tristate WriteString(byte x, byte y, String msg);
      virtual Tristate Misc(byte cmd, byte * data, byte length=0);

  protected:
};

#endif

#ifndef NEOPIXEL8H
#define NEOPIXEL8H

class Adafruit_NeoPixel8: public Grove_Display
{
  public:

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      // Index for if there are an array of actuators here.

      static String GetPins()
      {
          String msg="OK:Neopixel Display Pins:";
          msg.concat(NEOPIXEL_PINOUT);
          return msg;
      }

      static String GetListofMiscCmds()
      {
        String list ="Adafruit_NeoPixel8 Display Misc  Cmds:";
        int numCMDS = (int) NEOPIXELMiscCmds_MAX;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(NEOPIXELMiscCmdsArr[n]);
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      virtual Tristate Dummy();

      virtual Tristate Home();
      virtual Tristate Clear();

      virtual Tristate Backlight();
      virtual Tristate SetCursor(byte x, byte y);
      virtual Tristate WriteString(String msg);
      // No cursor and or no writestring:
      virtual Tristate CursorWriteStringAvailable();
      virtual Tristate WriteString(byte x, byte y, String msg);
      virtual Tristate Misc(byte cmd, byte * data, byte length=0); 

      int numPixels = NEOPIXEL_NUMPIXELS;
      int grovePin = NEOPIXEL_PIN;
      DeviceType deviceType = display;
    protected:
};
#endif

#ifndef CUSTOM_BARGRAPHH
#define CUSTOM_BARGRAPHH

#include "ic_74hc595_shiftRegister.h"

class Custom_Bargraph: public Grove_Display
{
  public:

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      // Index for if there are an array of actuators here.

      static String GetPins()
      {
        String msg="OK:Bargraph Display Pins:";
        msg.concat(GBARGRAPH_PINOUT);
        return msg;
      }

      static String GetListofMiscCmds()
      {
        String list ="Bargraph Display Misc  Cmds:";
        int numCMDS = (int) BARGRAPHMiscCmds_MAX;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(BARGRAPHMiscCmdsArr[n]);
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      virtual Tristate Dummy();

      virtual Tristate Home();
      virtual Tristate Clear();

      virtual Tristate Backlight();
      virtual Tristate SetCursor(byte x, byte y);
      virtual Tristate WriteString(String msg);
      // No cursor and or no writestring:
      virtual Tristate CursorWriteStringAvailable();
      virtual Tristate WriteString(byte x, byte y, String msg);
      virtual Tristate Misc(byte cmd, byte * data, byte length=0);
    protected:
      IC_74HC595_ShiftRegister * ic595;
};

#endif

#ifndef GROVE_BARGRAPHH
#define GROVE_BARGRAPHH

#include "ic_74hc595_shiftRegister.h"

class Grove_Bargraph: public Grove_Display
{
  public:



      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings);
      // Index for if there are an array of actuators here.

      static String GetPins()
      {
        String msg="OK:CustomBargraph Display Pins:";
        msg.concat(BARGRAPH_PINOUT);
        return msg;
      }

      static String GetListofMiscCmds()
      {
        String list ="Bargraph Display Misc  Cmds:";
        int numCMDS = (int) BARGRAPHMiscCmds_MAX;
        for (int n=0;n<numCMDS;n++)
        {
          
          String cmd = String(BARGRAPHMiscCmdsArr[n]);
          list.concat(cmd);
          if (n != (numCMDS-1))
            list.concat(',');
        }
        return list;
      }

      virtual Tristate Dummy();

      virtual Tristate Home();
      virtual Tristate Clear();

      virtual Tristate Backlight();
      virtual Tristate SetCursor(byte x, byte y);
      virtual Tristate WriteString(String msg);
      // No cursor and or no writestring:
      virtual Tristate CursorWriteStringAvailable();
      virtual Tristate WriteString(byte x, byte y, String msg);
      virtual Tristate Misc(byte cmd, byte * data, byte length=0);
    protected:
      IC_74HC595_ShiftRegister * ic595;
};

#endif
