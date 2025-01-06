#ifndef SoftataDevice_DHTXXH
#define SoftataDevice_DHTXXH
#include "SoftataDevice_sensor.h"
#include "SoftataDeviceInfo.h"

#include <float.h>
#define ERRORDBL  DBL_MAX;

class SoftataDevice_DHTXX: public SoftataDevice_Sensor
{
    public:
      SoftataDevice_DHTXX();
      SoftataDevice_DHTXX(int SetupPin);

      static String GetListofProperties()
      {
        String msg="";
        msg.concat(DHT11_PROPERTIES);
        return msg; 
      }

      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings=1);
      virtual String GetPins();

      virtual Tristate ReadAll(double * values);
      virtual String GetTelemetry();
      virtual double Read(int property);
      virtual CallbackInfo * GetCallbackInfo();
    protected:
      CallbackInfo info;
      int Pin;
      bool SetupPin(int pin);
};
#endif

#ifndef SoftataDevice_DH11H
#define SoftataDevice_DH11H
#include "SoftataDevice_sensor.h"
#include "SoftataDeviceInfo.h"

#include <float.h>
#define ERRORDBL  DBL_MAX;


class SoftataDevice_DHT11: public SoftataDevice_Sensor
{
    public:
      SoftataDevice_DHT11();
      SoftataDevice_DHT11(int SetupPin);

      static String GetListofProperties()
      {
        String msg="";
        msg.concat(DHT11_PROPERTIES);
        return msg; 
      }
      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings=1);
      virtual String GetPins();

      virtual Tristate ReadAll(double * values);
      virtual String GetTelemetry();
      virtual double Read(int property);
      virtual CallbackInfo * GetCallbackInfo();
    protected:
      CallbackInfo info;
      int Pin;
      bool SetupPin(int pin);
};
#endif

#ifndef SoftataDevice_BME280H
#define SoftataDevice_BME280H
#include "SoftataDevice_sensor.h"

class SoftataDevice_BME280: public SoftataDevice_Sensor
{
    public:
      SoftataDevice_BME280();

      static String GetListofProperties()
      {
        String msg="";
        msg.concat(BME280_PROPERTIES);
        return msg; 
      }
      virtual bool Setup();
      virtual bool Setup(byte * settings, byte numSettings=1);
      virtual String GetPins();

      virtual Tristate ReadAll(double * values);
      virtual String GetTelemetry();
      virtual double Read(int property);
      virtual CallbackInfo * GetCallbackInfo();
    protected:
      CallbackInfo info;
      bool SetupBME280();
};
#endif

#ifndef SoftataDevice_ULTRASONICRANGESENSORH
#define SoftataDevice_ULTRASONICRANGESENSORH
#include "SoftataDevice_sensor.h"


class SoftataDevice_URangeSensor : public SoftataDevice_Sensor
{
public:
    SoftataDevice_URangeSensor(int SetupPin);

    static String GetListofProperties()
    {
        String msg = "";;
        msg.concat(URANGE_PROPERTIES);
        return msg;
    }

    virtual bool Setup();
    virtual bool Setup(byte* settings, byte numSettings = 1);
    virtual String GetPins();

    virtual Tristate ReadAll(double* values);
    virtual String GetTelemetry();
    virtual double Read(int property);
    virtual CallbackInfo * GetCallbackInfo();    
    protected:
      CallbackInfo info;
    bool SetupURangeSensor();
};

class SoftataDevice_SensorSimulator : public SoftataDevice_Sensor
{
public:

    SoftataDevice_SensorSimulator();


    static String GetListofProperties()
    {
        String msg = "";
        msg.concat(SIMULATOR_PROPERTIES);
        return msg;
    }

    virtual bool Setup();
    virtual bool Setup(byte* settings, byte numSettings = 1);
    virtual String GetPins();
    
    virtual Tristate ReadAll(double* values);
    virtual String GetTelemetry();
    virtual double Read(int property);
    virtual CallbackInfo * GetCallbackInfo();    
    protected:
      CallbackInfo info;
};
#endif