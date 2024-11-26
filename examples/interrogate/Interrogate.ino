/***************************************************************
* Softata Example: Interrogate
****************************************************************
*
* Interrogate the API without connection to peripheral devices. 
* That is can instantiate a class but not call Setup()
*
****************************************************************/
#include <grove_sensor.h>
#include <grove_environsensors.h>
#include <grove_displays.h>
#include <grove_actuator.h>

byte relaySetup[] = {18};

void setup() {
  Serial.begin();
  while(!Serial);
  Serial.println(Grove::GetListofDevices());
  Serial.println();

  Serial.println(Grove_Sensor::GetListof());
  Serial.println(Grove_Sensor::GetListofCmds());
  Serial.println("====================");
  Serial.println(Grove_Sensor::GetName(BME280)); // Can get name for device without an instance
  Serial.println("====================");
  Serial.println(Grove_Sensor::GetPinout(BME280)); // Can get pinout for device without an instance
  Grove_BME280 * sensor = new Grove_BME280();
  Serial.println(sensor->GetPins());

  Serial.println("All Sensor Pinouts");
  for (int s = 0; s< SENSOR_NONE; s++)
  {
    Serial.print(s);
    Serial.print(". ");
    Serial.print(sensor_name[s]);
    Serial.print(": ");
    Serial.println(SENSOR_PINOUTS[s]);
  }

  //sensor->Setup();



  Serial.println();

  Serial.println(Grove_Display::GetListof());
  Serial.println(Grove_Display::GetListofCmds());
  Serial.println("====================");
  Serial.println(Grove_Display::GetName(NEOPIXEL)); // Can get name for device without an instance
  Serial.println("====================");
  Adafruit_NeoPixel8 * display = new Adafruit_NeoPixel8();
  Serial.println(Adafruit_NeoPixel8::GetPins());
  Serial.println(display->GetListofMiscCmds());
  
  Serial.println("All Display Pinouts");

  for (int d = 0; d< DISPLAY_NONE; d++)
  {
    Serial.print(d);
    Serial.print(". ");
    Serial.print(display_name[d]);
    Serial.print(": ");
    Serial.println(DISPLAY_PINOUTS[d]);
  }


  //display->Setup();
  Serial.println();
  
  // Get from class type
  Serial.println(Grove_Actuator::GetListof());
  Serial.println(Grove_Actuator::GetListofCmds());
  Serial.println("====================");
  Serial.println(Grove_Actuator::GetName(RELAY)); // Can get name for device without an instance
  Serial.println("====================");
  // Get from specfic class
  Serial.println(Grove_Relay::GetPins()); 
  Grove_Relay * relay  = new  Grove_Relay();
  // Can also get these again from the instance
  Serial.println(relay->GetListofCmds());
  Serial.println(relay->GetPins());
  // And from index
  Serial.print("Relay (enum) ord: ");
  Serial.println(RELAY);
  Serial.println(ACTUATOR_PINOUTS[RELAY]);


  Serial.println("All Actuator Pinouts");
  for (int a = 0; a<ACTUATOR_NONE; a++)
  {
    Serial.print(a);
    Serial.print(". ");
    Serial.print(actuator_name[a]);
    Serial.print(": ");
    Serial.println(ACTUATOR_PINOUTS[a]);
  }

  
  //relay->Setup->(relaySetup,1);

}

void loop() {


}

/*************************
DEVICES:sensor,actuator,communication,display,serial

SENSORS:DHT11,BME280,UltrasonicRanger,Simulator,DHTXX
Sensor Cmds:getpins,getProperties,setupdefault,setup,readall,read,getTelemetry,sendTelemetryBT,sendTelemetryToIoTHub,pause_sendTelemetry,continue_sendTelemetry,stop_sendTelemetry,getSensors
OK:BME280 Sensor Pins:I2C0 (Pins8/9 (SDA/SCL) fixed): Address 0x77 (Alt 0x76). Embedded in driver though.

Displays:OLED096,LCD1602,NEOPIXEL,BARGRAPH,GBARGRAPH
Display Cmds:getCmds,getDisplays,getpins,setupDefault,setup,dispose,miscGetList,clear,backlight,setCursor,writestring,cursor_writestring,home,dummy,misc
OK:Neopixel Display Pins:OneWire: Pin 16 (default) Alt 18 or 20 (Grove yellow cable).. 17,19,21 (Grove white cable)
Neopixel Display Misc  Cmds:setpixelcolor,setpixelcolorAll,setpixelcolorOdds,setpixelcolorEvens,setBrightness,setN,NEOPIXELMiscCmds_MAX

ACTUATORS:SERVO,SIPO_74HC595,RELAY
Actuator Cmds:getpins,getValueRange,setupDefault,setup,writeDoubleValue,writeByteValue,writeWordValue,SetBitState,SetBit,ClearBit,ToggleBit,getActuators
OK:Relay PinsPin 16 (default), 18 or 20
OK:Relay PinsPin 16 (default), 18 or 20

*************************/
