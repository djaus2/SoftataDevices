#include "SoftataDevice_environsensors.h"
#include <arduino.h>
#include <dht.h>
#include "SoftataDeviceInfo.h"


#ifdef SoftataDevice_RPI_PICO_SHIELD
#define NUM_PINS 3
#define DEFAULT_PIN DHT11Pin_D
#define PINS 16,18,20
#define pins "16,18,20"
int Pins[] = {PINS};
#elif defined(RPI_PICO_DEFAULT)
#define DEFAULT_PIN DHT11Pin_D
#define PIN_START 0
#define PIN_END 26
#define pins "Any of GPIO 0 to 26"
#endif


    



    SoftataDevice_DHT11::SoftataDevice_DHT11()
    {
      SoftataDevice_Sensor::num_properties = NUM_DHT11_PROPERTIES;
      SoftataDevice_Sensor::sensorType = DHT11;
    }

    SoftataDevice_DHT11::SoftataDevice_DHT11(int pin)
    {
      Pin = pin;
      SetupPin(Pin);
      SoftataDevice_Sensor::num_properties = NUM_DHT11_PROPERTIES;
      SoftataDevice_Sensor::sensorType = DHT11;
    }

    String SoftataDevice_DHT11::GetPins()
    {
      String _pins = String("DHT11 Sensor Pins:");
      _pins.concat(pins);
      _pins.concat(" Default:");
      _pins.concat(DEFAULT_PIN);
      Serial.println(_pins);
      return String(_pins); //pins;
    }


    bool SoftataDevice_DHT11::SetupPin(int pin)
    {
      // Check that the nominated pin is valid
      bool found = false;
#ifdef SoftataDevice_RPI_PICO_SHIELD
      for (int i=0;i<NUM_PINS;i++)
      {
        if(pin == Pins[i])
        {
          found= true;
          break;
        }
      }
#elif defined(RPI_PICO_DEFAULT)
      if ((pin>=PIN_START) && (pin<=PIN_END))
        found = true;
#endif
      if(!found)
        return false;

      //Set the DHT11 pin
      Pin = pin;
      while(!Serial){delay(100);};
      Serial.println("DHT Grove");
      Serial.print("LIBRARY VERSION: ");
      Serial.println(DHT_LIB_VERSION);
      Serial.println();
      //Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
      return true;
    }

  

    bool SoftataDevice_DHT11::Setup(byte * settings, byte numSettings)
    {
      if(numSettings>0)
      {
        Pin = settings[0];
        return SetupPin(Pin);
      }
      else
        return false;
    }
 
    bool SoftataDevice_DHT11::Setup()
    {
      Pin = DEFAULT_PIN;
      return SetupPin(Pin);
      num_properties = 2;
    }



    Tristate SoftataDevice_DHT11::ReadAll(double * values)
    {
      dht DHT;
      // READ DATA
      Serial.print("DHT11:");
      // Allow 3 retries
      bool OK = false;
      for (int i=0;i<4;i++)
      {
        int chk = DHT.read11(Pin);
        switch (chk)
        {
          case DHTLIB_OK:  
          Serial.println("OK"); 
          OK = true;
          break;
          case DHTLIB_ERROR_CHECKSUM: 
          Serial.println("Checksum error"); 
          break;
          case DHTLIB_ERROR_TIMEOUT: 
          Serial.println("Time out error"); 
          break;
          default: 
          Serial.println("Unknown error"); 
          break;
        }
        if(OK)
          break;
        delay(100);
        if(OK)
          break;
      }
      if(!OK)
        return (Tristate)false;
      // DISPLAY DATA
      values[0] = DHT.temperature;
      values[1] = DHT.humidity;
      return (Tristate)true;
    }

    String SoftataDevice_DHT11::GetTelemetry()
    {
      double values[2];
      if(ReadAll(values))
      {
        String msg ="{\"temperature\":";
        msg.concat(values[0]);
        msg.concat(',');
        msg.concat("\"humidity\":");
        msg.concat(values[1]);
        msg.concat('}');
        return msg;
      }
      else
        return "ERRORDBL";
}

CallbackInfo * SoftataDevice_DHT11::GetCallbackInfo()
{
    info.period = 314159;
    info.next = 137;
    info.SensorIndex = 123456;
    info.sendBT = false;
    info.isSensor=false;
    info.isRunning=false;
    return &info;
}

    double SoftataDevice_DHT11::Read(int property)
    {
      dht DHT;
      // READ DATA
      Serial.print("DHT11:");
      
      // Allow 3 retries
      bool OK = false;
      for (int i=0;i<4;i++)
      {
        int chk = DHT.read11(Pin);
        switch (chk)
        {
          case DHTLIB_OK:  
          Serial.println("OK,"); 
          OK = true;
          break;
          case DHTLIB_ERROR_CHECKSUM: 
          Serial.println("Checksum error"); 
          break;
          case DHTLIB_ERROR_TIMEOUT: 
          Serial.println("Time out error"); 
          break;
          default: 
          Serial.println("Unknown error"); 
          break;
        }
        if(OK)
          break;
        delay(100);
      }
      if(!OK)
        return ERRORDBL;
      // DISPLAY DATA
      switch(property)
      {
        case 0:
          return DHT.temperature;
          break;
        case 1: 
          return DHT.humidity;
          break; 
        default:
          return ERRORDBL;
          break;
      }
    }


