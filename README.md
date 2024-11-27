# Softata
Updared base Arduino Softata code from [Soft-ata repository](https://github.com/djaus2/Soft-ata)

This is the Arduino code for interacting with devices from a Raspbery Pi Pico W. The top level code that orchestrates the remote interaction with these devices is separated an not included here. That remains (subject to an 

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

The files in this repository are those from the src folder from the Softata Sketch in the Softa-ata repository _( see below)_  plus some from the root of the sketch folder. The Soft-ata repsository needs to be modified so as remove the src folder from this Softata folder plus those extra files, and for the softatta sketvch there to to reference this repository.

## Sample Code
There is one example sketch thus far in the examples folder, interrogate. This will run on a RPi Pico W configured for Arduino and return information about supported devices without actually needing any to be connected.

## Usage
Download the zip file, ``` [Code]-Clone-Download Zip```, green button top right when at root of the repository in GitHub.
Create a new sketch then Sketch->Include Library->Add zip file and browse to the downloaded zip file


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

