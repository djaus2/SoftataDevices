# Softata
Updared base Arduino Softata code from [Soft-ata repository](https://github.com/djaus2/Soft-ata)

> This is the Arduino code for interacting with devices from a Raspbery Pi Pico W. The top level code that orchestrates the remote interaction with these devices is not included here. That remains in the Softa-ata repsository in the Softata sketch there and  is subject to an update for this.

Devices are from one of the following classes

```
                | - Actuators
SoftatDevice -  | - Sensors
                | - Displays
```

- Each of the 3 device types on the right inherit common properties from the SoftatDevice class.
- Each of the classes on the right have specific properties as well
  - Some of the device class propeties as universal from all devices of that type
    - If no relevant for a spoecific device in a device type then the method is a dummy and returns without error.
  - Some device class properties are specific to the device
    - In particular, the Display clases have a Misc set of methods that are specific to each display type.

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

The files in this repository are those from the src folder from the Softata Sketch in the Softa-ata repository _( see below)_  plus some from the root of the sketch folder. The Soft-ata repsository needs to be modified so as remove the src folder from this Softata folder plus those extra files, and for the softatta sketvch there to to reference this repository.

## Sample Code
There is one example sketch thus far in the examples folder, interrogate. This will run on a RPi Pico W configured for Arduino and return information about supported devices without actually needing any to be connected.

## Usage
Download the zip file, ``` [Code]-Clone-Download Zip```, green button top right when at root of the repository in GitHub.
Create a new sketch then Sketch->Include Library->Add zip file and browse to the downloaded zip file.
The required includes are as per the ```interrogate``` sketch:

```cpp
#include <grove_sensor.h>
#include <grove_environsensors.h>
#include <grove_displays.h>
#include <grove_actuator.h>
```

You may wish to add ```grove.h```

## Notes:

There are added features in this Softaata API compared to that in Softa-ata. These changes are meant to keep knowledge of devices in the sketch code such that the remote code can interrogate the device to determine what it can orchestrate minimising the knowledge of Softata that the remote application needs to have.


## Soft-ata/Softata Sketch Code
```
Softata
│   Connect2WiFi.cpp
│   Connect2WiFi.h
│   devicesLists.h
│   iothub.h
│   menu.cpp
│   menu.h
│   NetworkSettings.h
│   readme.md
│   rpiboards.h
│   rpiwatchdog.c
│   rpiwatchdog.h
│   serial_macros.h
│   Softata.h
│   Softata.ino
│   SoftataCore2.h
│   SoftataOTA.h
│
└───src
    │   adrafruit_neopixel_display.cpp
    │   custom_bargraph_display.cpp
    │   grove.h
    │   grove_actuator.h
    │   grove_bargraph.cpp
    │   grove_bme280.cpp
    │   grove_dht11.cpp
    │   grove_dhtxx.cpp
    │   grove_displays.h
    │   grove_environsensors.h
    │   grove_OLED_096_display.cpp
    │   grove_relay.cpp
    │   grove_rgb_lcd_display.cpp
    │   grove_sensor.h
    │   grove_sensorsimulator.cpp
    │   grove_urange.cpp
    │   ic_74hc595_shiftRegister.cpp
    │   ic_74hc595_shiftRegister.h
    │   servo.cpp
    │   SIPO_74HC595.cpp
    │
    └───
```


fffgg

