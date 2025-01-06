#include <Arduino.h>
#include <U8g2lib.h>
//Navigate to Sketch -> Include Library -> Manage Libraries... 
//Search and Install U8g2 library in the Library Manager.
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "SoftataDevice_display.h"


/////////////////////////////////////////////////////////////////////
// Grove-LCD RGB Backlight  V2.00
// https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
/////////////////////////////////////////////////////////////////////
// Install Grove-LCD RGB Backlight by Seeed Studio
// https://github.com/Seeed-Studio/SoftataDevice_LCD_RGB_Backlight
/////////////////////////////////////////////////////////////////////
//https://github.com/DFRobot/DFRobot_RGBLCD1602

#include "rgb_lcd.h"

rgb_lcd lcd;

// Default backlight
#define COLORRED  128
#define COLORGREEN  128
#define COLORBLUE  128



bool SoftataDevice_LCD1602::Setup()
{
  this->DisplayType = LCD1602;
  SoftataDevice::SetI2CPins(0);
  lcd.begin(16, 2);
  lcd.setRGB(COLORRED, COLORGREEN, COLORBLUE);
  return true;
}

bool SoftataDevice_LCD1602::Setup(byte * settings, byte numSettings)
{
  this->DisplayType = LCD1602;
  if (numSettings>1)
  {
    int i2c = settings[0];
    if((i2c==0) || (i2c==1))
    {
      int colorRed = COLORRED;
      int colorGreen = COLORGREEN;
      int colorBlue = COLORBLUE;
      SoftataDevice::SetI2CPins(i2c);
      lcd.begin(16, 2);
      if (numSettings>3)
      {
          bool testRed = (settings[1]>-1)&&(settings[1]<256);
          bool testGreen = (settings[2]>-1)&&(settings[2]<256);
          bool testBlue = (settings[3]>-1)&&(settings[3]<256);
          if(testRed&&testGreen&&testBlue)
          {
            colorRed = settings[1];
            colorGreen = settings[2];
            colorBlue = settings[3];
          }
          lcd.setRGB(colorRed, colorGreen, colorBlue);
      }
      return false;
    }
    else
      return false;
  }
  return true;
}



Tristate SoftataDevice_LCD1602::Dummy()
{
  return notImplemented;
}

Tristate SoftataDevice_LCD1602::Clear()
{
  lcd.clear();
  return (Tristate)true;;
}

Tristate SoftataDevice_LCD1602::Home()
{
  lcd.home();
  return (Tristate)true;
}


Tristate SoftataDevice_LCD1602::SetCursor(byte x, byte y)
{
  // Note: line 1 is the second row, since counting begins with 0:
  lcd.setCursor(x,y);
  return (Tristate)true;
}

Tristate SoftataDevice_LCD1602::WriteString(String msg)
{
  lcd.print(msg.c_str());
  return (Tristate)true;
}

// No setcursor and/or no writestring
Tristate SoftataDevice_LCD1602::CursorWriteStringAvailable()
{
	return (Tristate)true;
}

Tristate SoftataDevice_LCD1602::WriteString(byte x, byte y, String msg)
{
  // Note: line 1 is the second row, since counting begins with 0:
  lcd.setCursor(x,y);
  lcd.print(msg.c_str());
  return (Tristate)true;
}

Tristate SoftataDevice_LCD1602::Misc(byte cmd, byte * data, byte length)
{
  if (cmd<0)
    return (Tristate)false;
  else if(cmd>(int) LCD1602MiscCmds_MAX)
    return (Tristate)false;
  LCD1602MiscCmds Cmd = (LCD1602MiscCmds)cmd;
  switch (cmd)
  {

  case autoscrollon:
      Serial.print("Autoscroll:");
      Serial.println(cmd);
      lcd.autoscroll();
      break;
  case noautoscroll:
      Serial.print("noautoscroll:");
      Serial.println(cmd);
      lcd.noAutoscroll();
      break;
  case blinkon:
      Serial.print("blink:");
      Serial.println(cmd);
      lcd.blink();
      break;
  case noblink:
      Serial.print("nonlink:");
      Serial.println(cmd);
      lcd.noBlink();
      break;
  case LCD1602MiscCmds_MAX:
      Serial.print("Max:");
      Serial.println(cmd);
      return (Tristate)false;
      break;
  default:
      Serial.print("Default:");
      Serial.println(cmd);
      return (Tristate)false;
      break;
  }
  return (Tristate)true;
}


// Not relevant for SoftataDevice_LCD1602
Tristate SoftataDevice_LCD1602::Backlight()
{
  return notImplemented;;
}







