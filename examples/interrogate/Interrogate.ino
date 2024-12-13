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
  Serial.println(SoftataDevice_Sensor::_GetListofProperties(BME280)); // Get from device type class using device ordinal
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
  Serial.println(SoftataDevice_Display::_GetListofMiscCmds(NEOPIXEL));  // Get from device type class using device ordinal
  Serial.println("====================");
  Serial.println(Adafruit_NeoPixel8::GetPins());             // Get from specific device class
  Adafruit_NeoPixel8 * display = new Adafruit_NeoPixel8();   // Instantiate specific device
  //SoftataDevice_Display * display = SoftataDevice_Display::_Setup(NEOPIXEL);  // Instantiate specific device via Display class method using device ordinal
  Serial.println(display->_GetListofMiscCmds(NEOPIXEL));              // Get from device instance

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


