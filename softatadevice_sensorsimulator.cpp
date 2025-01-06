#include "SoftataDevice_environsensors.h"
#include <arduino.h>

#include "SoftataDeviceInfo.h"


#ifdef SoftataDevice_RPI_PICO_SHIELD
// Insert, see DHT11 and BME280
#elif defined(RPI_PICO_DEFAULT)
// Insert, see DHT11 and BME280
#endif






    SoftataDevice_SensorSimulator::SoftataDevice_SensorSimulator()
    {
      //Any class instantiation
      sensorType = Simulator;
      num_properties = NUM_SIMULATOR_PROPERTIES;
    }

  

    bool SoftataDevice_SensorSimulator::Setup(byte * settings, byte numSettings)
    {
      randomSeed(analogRead(0));
      return true;
    }
 
    bool SoftataDevice_SensorSimulator::Setup()
    {
      randomSeed(analogRead(0));
      return true;
    }

    String SoftataDevice_SensorSimulator::GetPins()
    {
        String msg = "Simulator Sensor Pins:";
        msg.concat(SIMULATOR_PINOUT);
        return msg;
    }

    
    Tristate SoftataDevice_SensorSimulator::ReadAll(double * values)
    {
      //Read all values and assign to values array eg:
      values[0] = Read(0);
      return notImplemented;  //Deliberate error
    }

    String SoftataDevice_SensorSimulator::GetTelemetry()
    {
      double values[NUM_SIMULATOR_PROPERTIES];
      // Return 10.00 +- upto 1.00
      double val = 10.00;
      double diff = random(0,100)-50;
      diff /= 50;
      val += diff;
      values[0] = val;
      if(ReadAll(values))
      {
        String msg="{\"temperature\":";
        //Construct json string from num_properties
        // See DHT11 and BME280
        msg.concat(values[0]);
        msg.concat("}");
        return msg;
      }
      else
        return "ERRORDBL";
}

CallbackInfo * SoftataDevice_SensorSimulator::GetCallbackInfo()
{
    info.period = 314159;
    info.next = 137;
    info.SensorIndex = 123456;
    info.sendBT = false;
    info.isSensor=false;
    info.isRunning=false;
    return &info;
}

  double SoftataDevice_SensorSimulator::Read(int property)
  {
    // Read and return the nth property
    // Might need to readall then select int
    // See DHT11 and BME280
    // Return 10.00 +- upto 1.00
    double val = 10.00;
    double diff = random(0,100)-50;
    diff /= 50;
    val += diff;
    return val;
  }


