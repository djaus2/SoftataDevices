## SoftataDevices

Updared base Arduino Softata code from the GitHub [djaus2/Soft-ata](https://github.com/djaus2/Soft-ata) repository.

> This is the Arduino code for interacting with devices from a Raspbery Pi Pico W. The top level code that orchestrates the remote interaction with these devices is not included here. That remains in the Softa-ata repsository in the Softata sketch there and  is subject to an update for this.

**Refactoring:**
_From another perspective_ This is a refeactoring of the repository [djaus2/Soft-ata](https://gitshub.com/Softata) such that ```<repo>/code/Softata/src``` directory is separated to here.
[See Refactoring below](#Refactoring)

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

```cppsoftatadevice_sensor
#include <.h>
#include <softatadevice_environsensors.h>
#include <softatadevice_displays.h>
#include <softatadevice_actuator.h>
```

You may wish to add ```softatadevice.h```

====

## Refactoring  

*Restatement:** A refactoring of the repository [djaus2/Soft-ata](https://gitshub.com/Softata) such that ```<repo>/code/Softata/src``` directory is separated to here.

This refactored version of that folder so that it is a separate Arduino library.

It can be installed from an Arduino sketch by downloading the zip file (press to green Clone button) and installing it as a zip file librray.

Previously this folder sat below the root of the Arduino softata sketch folder. It is confiured as a hierachy of classes so that a device class inherits methods from defined in the parent and so that all classes antecendant from the same parent have the same methods, but with device specific implementations. For example, all displays implement the ```Clear()``` method. Also, all displays implement a ```Misc()``` method that has methods specific to the display type. For example, the bargraph has a misc.floww() method that turns on every odd segenment. 

Methods that do not return a value (such as with a sensor read), return a tristate enum value which is normally ```_ok```. If there is an error in the method, ```_nok``` is returned. If a method is not implemneted then ```notimplemneted``` is returned which at a higher level is meant to be interpretteed is OK but can be used otherwise. ```_nan_``` is alos a return option for data reads.
one 

====

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
└───src : ***Moved to this repository:***
    │   adrafruit_neopixel_display.cpp
    │   custom_bargraph_display.cpp
    │   grove.h
    │   softatadevice_actuator.h
    │   softatadevice_bargraph.cpp
    │   softatadevice_bme280.cpp
    │   softatadevice_dht11.cpp
    │   softatadevice_dhtxx.cpp
    │   softatadevice_displays.h
    │   softatadevice_environsensors.h
    │   softatadevice_OLED_096_display.cpp
    │   softatadevice_relay.cpp
    │   softatadevice_rgb_lcd_display.cpp
    │   softatadevice_sensor.h
    │   softatadevice_sensorsimulator.cpp
    │   softatadevice_urange.cpp
    │   ic_74hc595_shiftRegister.cpp
    │   ic_74hc595_shiftRegister.h
    │   servo.cpp
    │   SIPO_74HC595.cpp
    │
    └───
```



