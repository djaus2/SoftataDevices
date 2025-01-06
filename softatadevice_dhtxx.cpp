#include "SoftataDevice_environsensors.h"
#include <arduino.h>
#include <dhtnew.h>
#include "SoftataDeviceInfo.h"


#ifdef SoftataDevice_RPI_PICO_SHIELD
#define XNUM_PINS 3
#define XDEFAULT_PIN DHT11Pin_D
#define XPINS 16,18,20
#define Xpins "16,18,20"
int XPins[] = {XPINS};
#elif defined(RPI_PICO_DEFAULT)
#define XDEFAULT_PIN DHT11Pin_D
#define PIN_START 0
#define PIN_END 26
#define pins "Any of GPIO 0 to 26"
#endif


    
   DHTNEW * mySensor = NULL;
   static int minTimeBtwReads_ms = DHTXX_MIN_TIME_BTW_READS_MS;

    SoftataDevice_DHTXX::SoftataDevice_DHTXX()
    {
      SoftataDevice_Sensor::num_properties = NUM_DHTXX_PROPERTIES;
      SoftataDevice_Sensor::sensorType = DHTXX;
    }

    SoftataDevice_DHTXX::SoftataDevice_DHTXX(int pin)
    {
      Pin = pin;
      SetupPin(Pin);
      SoftataDevice_Sensor::num_properties = NUM_DHTXX_PROPERTIES;
      SoftataDevice_Sensor::sensorType = DHTXX;
    }

    String SoftataDevice_DHTXX::GetPins()
    {
      String _pins = String("DHTXX Sensor Pins:");
      _pins.concat(Xpins);
      _pins.concat(" Default:");
      _pins.concat(XDEFAULT_PIN);
      Serial.println(_pins);
      return String(_pins); //pins;
    }


    bool SoftataDevice_DHTXX::SetupPin(int pin)
    {
      // Check that the nominated pin is valid
      bool found = false;
#ifdef SoftataDevice_RPI_PICO_SHIELD
      for (int i=0;i<XNUM_PINS;i++)
      {
        if(pin == XPins[i])
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
      mySensor = new DHTNEW(Pin);
      while(!Serial){delay(100);};
      Serial.print("DHT");
      Serial.print(mySensor->getType());
      Serial.println(" Grove");
      Serial.print("LIBRARY VERSION: ");
      Serial.println(DHTNEW_LIB_VERSION);
      Serial.println();
      //Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
      return true;
    }

  

    bool SoftataDevice_DHTXX::Setup(byte * settings, byte numSettings)
    {
      if(numSettings>0)
      {
        Pin = settings[0];
        return SetupPin(Pin);
      }
      else
        return false;
    }
 
    bool SoftataDevice_DHTXX::Setup()
    {
      Pin = XDEFAULT_PIN;
      return SetupPin(Pin);
      //num_properties = NUM_DHTXX_PROPERTIES;
    }



    Tristate SoftataDevice_DHTXX::ReadAll(double * values)
    {
      // READ DATA
      Serial.print("DHT");
      Serial.println(mySensor->getType());
      // Allow 3 retries
      bool OK = false;
      // Don't reread too soon
      if((millis() - mySensor->lastRead()) >= minTimeBtwReads_ms)
      {
        for (int i=0;i<10;i++)
        {
          // Wait
          while((millis() - mySensor->lastRead()) < minTimeBtwReads_ms)
            delay(50);
          Serial.println("Reading DHTXX");
          int chk = mySensor->read();
          Serial.print("Returned: ");
          Serial.println(chk);
          switch (chk)
          {
            case DHTLIB_OK:
              Serial.println("OK,\t");
              OK=true;
              break;
            case DHTLIB_ERROR_CHECKSUM:
              Serial.print("Checksum error,\t");
              break;
            case DHTLIB_ERROR_TIMEOUT_A:
              Serial.print("Time out A error,\t");
              break;
            case DHTLIB_ERROR_TIMEOUT_B:
              Serial.print("Time out B error,\t");
              break;
            case DHTLIB_ERROR_TIMEOUT_C:
              Serial.print("Time out C error,\t");
              break;
            case DHTLIB_ERROR_TIMEOUT_D:
              Serial.print("Time out D error,\t");
              break;
            case DHTLIB_ERROR_SENSOR_NOT_READY:
              Serial.print("Sensor not ready,\t");
              break;
            case DHTLIB_ERROR_BIT_SHIFT:
              Serial.print("Bit shift error,\t");
              break;
            case DHTLIB_WAITING_FOR_READ:
              Serial.print("Waiting for read,\t");
              break;
            default:
              Serial.print("Unknown: ");
              Serial.print(chk);
              Serial.print(",\t");
              break;
          }
          if(OK)
            break;
          else
          // If fail then increase minTimeBtwReads_ms
          minTimeBtwReads_ms += DHTXX_MIN_TIME_BTW_READS_MS_INCR;
          Serial.println(minTimeBtwReads_ms);
          delay(100);
        }

      }
      else {
        OK = true;
      }
      if(!OK)
        return (Tristate)false;
      // DISPLAY DATA
      values[0] = mySensor->getTemperature();
      values[1] = mySensor->getHumidity();
      return (Tristate)true;
    }

    String SoftataDevice_DHTXX::GetTelemetry()
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

    CallbackInfo * SoftataDevice_DHTXX::GetCallbackInfo()
    {
        info.period = 314159;
        info.next = 137;
        info.SensorIndex = 123456;
        info.sendBT = false;
        info.isSensor=false;
        info.isRunning=false;
        return &info;
    }

    double SoftataDevice_DHTXX::Read(int property)
    {
      Serial.println("ReadAll()");
      if((property<0) || (property>1))
      {
        Serial.println("ReadAll() Invalid property");
        return ERRORDBL;
      }
      double values[2];
      if(ReadAll(values))
      {
        Serial.println("ReadAll() Done");
        return values[property];
      }
      else {
        Serial.println("ReadAll() Fail");
        return ERRORDBL;
      }
    }

