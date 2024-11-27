# Softata
Updared base Arduino Softata code from Soft-ata repository

This is the arduino code for interacting with devices from a Raspbery Pi Pico W.

Devices are from one of the following classes

```
                | - Actuators
SoftatDevice -  | - Sensors
                | - Displays
```

- Each of the 3 device types on the right inherit commomn properties from the Grove class.
- Each of the classes on the right have specific properties as well
  - Some of the device class propeties as universal from all deviecs of that type
  - Some device class properties are specific to the device

**The full list of the implemented devices follows:**

```
SoftataDevice
|
├───Actuator
│       Relay
│       Servo
│       Sipo
│
├───Display
│       Bargraph
│       GBargraph
│       LCD1602
│       NEOPIXEL
│       OLED096
│
└───Sensor
        BME280
        DHT11
        DHTXX
        Simulator
        UltrasonicRanger
```

