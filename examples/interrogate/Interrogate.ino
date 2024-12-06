/***************************************************************
* Softata Example: Interrogate
****************************************************************
*
* Interrogate the API without connection to peripheral devices. 
* Can instantiate a class without calling Setup().
*
****************************************************************/
#include <softatadevice.h>
#include <softataDevice_sensor.h>
#include <SoftataDevice_environsensors.h>
#include <SoftataDevice_display.h>
#include <SoftataDevice_actuator.h>

byte relaySetup[] = {18};

void setup() {
  Serial.begin();
  while(!Serial);
  Serial.println(SoftataDevice::GetListofDevices());                  // Get from general device class
  Serial.println();
  
  Serial.println(SoftataDevice_Sensor::GetListofDevices());           //Get from device type class 
  Serial.println(SoftataDevice_Sensor::GetListofCmds());              //Get from device type class, cmds common to the device type
  Serial.println("====================");
  Serial.println(SoftataDevice_Sensor::GGetListofProperties(BME280)); // Get from device type class using device ordinal
  Serial.println(SoftataDevice_Sensor::GetListofProperties(BME280));  // Get from device type class using device ordinal
  Serial.println(SoftataDevice_Sensor::GetName(BME280));              // Get from device type class using device ordinal
  Serial.println(SoftataDevice_Sensor::GetPinout(BME280));            // Get from device type class using device ordinal
  Serial.println("====================");
  Serial.println(SoftataDevice_BME280::GetListofProperties());        // Get from specific device class
  SoftataDevice_BME280 * sensor = new SoftataDevice_BME280();         // Instantiate specofic device
  Serial.println(sensor->GetPins());                                  // Get from device instance


  Serial.println("All Sensor Pinouts");
  for (int s = 0; s< SENSOR_NONE; s++)
  {
    Serial.print(s);
    Serial.print(". ");
    Serial.print(sensor_name[s]);               // Macro generated array of strings indexed by device type -> device ordibnal
    Serial.print(": ");
    Serial.println(SENSOR_PINOUTS[s]);          // Macro generated array os strings indexed by device type -> device ordibnal
  }

  //sensor->Setup();



  Serial.println();

  Serial.println(SoftataDevice_Display::GetListofDevices()); // Get from device type class
  Serial.println(SoftataDevice_Display::GetListofCmds());    // Get from device type class, cmds common to the device type
  Serial.println("====================");
  Serial.println(SoftataDevice_Display::GetName(NEOPIXEL));  // Get from device type class using device ordinal
  Serial.println("====================");
  Adafruit_NeoPixel8 * display = new Adafruit_NeoPixel8();   // Instantiate specofic device
  Serial.println(Adafruit_NeoPixel8::GetPins());             // Get from specific device class 
  Serial.println(display->GetListofMiscCmds());              // Get from device instance
  
  Serial.println("All Display Pinouts");

  for (int d = 0; d< DISPLAY_NONE; d++)
  {
    Serial.print(d);
    Serial.print(". ");
    Serial.print(display_name[d]);                           // Macro generated array of strings indexed by device type -> device ordibnal
    Serial.print(": ");
    Serial.println(DISPLAY_PINOUTS[d]);                      // Macro generated array of strings indexed by device type -> device ordibnal
  }


  //display->Setup();
  Serial.println();
  
  // Get from class type
  Serial.println(SoftataDevice_Actuator::GetListofDevices()); //Get from device type class
  Serial.println(SoftataDevice_Actuator::GetListofCmds());    //Get from device type class, cmds common to the device type
  Serial.println("====================");
  Serial.println(SoftataDevice_Actuator::GetName(RELAY));     // Get from device type class using device ordinal
  Serial.println("====================");
  // Get from specfic class
  Serial.println(SoftataDevice_Relay::GetPins());             // Get from specific device class
  SoftataDevice_Relay * relay  = new  SoftataDevice_Relay();  // Instantiate specofic device
  // Can also get these again from the instance
  Serial.println(relay->GetListofCmds());                     // Get from device instance
  Serial.println(relay->GetPins());                           // Get from device instance
  // And from index
  Serial.print("Relay (enum) ord: ");                         // Show device ordinal from enum device type list
  Serial.println(RELAY);                                      // ''
  Serial.println(ACTUATOR_PINOUTS[RELAY]);                    // Macro generated array of strings indexed by device type -> device ordibnal


  Serial.println("All Actuator Pinouts");
  for (int a = 0; a<ACTUATOR_NONE; a++)
  {
    Serial.print(a);
    Serial.print(". ");
    Serial.print(actuator_name[a]);               // Macro generated array of strings indexed by device type -> device ordibnal
    Serial.print(": ");
    Serial.println(ACTUATOR_PINOUTS[a]);          // Macro generated array of strings indexed by device type -> device ordibnal
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
OK:Neopixel Display Pins:OneWire: Pin 16 (default) Alt 18 or 20 (Softatadevice yellow cable).. 17,19,21 (Softatadevice white cable)
Neopixel Display Misc  Cmds:setpixelcolor,setpixelcolorAll,setpixelcolorOdds,setpixelcolorEvens,setBrightness,setN,NEOPIXELMiscCmds_MAX

ACTUATORS:SERVO,SIPO_74HC595,RELAY
Actuator Cmds:getpins,getValueRange,setupDefault,setup,writeDoubleValue,writeByteValue,writeWordValue,SetBitState,SetBit,ClearBit,ToggleBit,getActuators
OK:Relay PinsPin 16 (default), 18 or 20
OK:Relay PinsPin 16 (default), 18 or 20

*************************/
