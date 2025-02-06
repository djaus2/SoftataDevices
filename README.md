## SoftataDevices

----

### Updates
- Added 74HC165 8/16 Bit Parallel In Serial Out (To micro) _Now works for 1 byte. 2 bytes not yet implemented. (Close)_
- Added Grove single LED and new device class DeviceInput with (Grove) Switch. _Multibit input coming_
- Added ActuatorCapabilities property to each actuator to indicate which actuator methods apply and hence what data is required.
  - Once instantiated, actuator can be queried for this property
  - SoftataConsole2 app then can determine what data (byte/bit/none) is required for a method call.  
  ```enum actuatorcapabilities {a_singlebit,a_bitonly,a_writeonly,a_both}```
- Added QuadRelays: Bank of 4  bit manipulated relays. Could be used as any 4 bit digital output.
  - Can also write a byte value to set/clr all 4 bits in one call.
  - ToDo: Set number of bits/relqays
  - Note 4 bits use 4 consecutive GPIO ports, setup only needs first (default 16).
 
----

Updared base Arduino Softata code from the GitHub [djaus2/Soft-ata](https://github.com/djaus2/Soft-ata) repository.

> This is the Arduino code for interacting with devices from a Raspbery Pi Pico W. The top level code that orchestrates the remote interaction with these devices is not included here. That remains in the Softa-ata repsository in the Softata sketch there and  is subject to an update for this.  
> Soft-ata/code/***SoftaaConsole2*** app exercises this library. 

**Refactoring:**
_From another perspective_ This is a refactoring of the repository [djaus2/Soft-ata](https://gitshub.com/Softata) such that ```<repo>/code/Softata/src``` directory is separated to here.
[See Refactoring](#Refactoring) below.

> Note the Grove name as used previousy has been changed to SoftataDevices.

Devices are from one of the following classes

```
                 | - Actuators
SoftataDevice -  | - Sensors
                 | - Displays
                 | - Inputs (Switches etc) Coming
```

- Each of the 3 device types on the right inherit common properties and methods from the SoftatDevice class.
  - For example, all devices implement a default Setup().
  - Also, all antecedant device classes include GetListofDevices() to get a current csv list of implemented devices of thaat device type.
    - For the top level class SoftataDevice , GetListofDevices() returns a csv list of the device types.
- Each of the classes on the right have specific properties as well
  - Some of the device class propeties are universal from all devices of that type
    - If no relevant for a specific device in a device type then the method is a dummy and returns without error.
  - Some device class properties are specific to the device
    - In particular, the Display clases have a Misc set of methods that are specific to each display type.

**The full list of the implemented devices follows:**

```
SoftataDevice
|
├───Actuator
│       (Grove) Relay
│       Servo
│       Sipo (74HC595) 8/16 Bit Serial In (from Micro) Parallel Out
│       QuadRelay (Generic)
|       (Grove) LED
│
├───Display
│       Bargraph (using Sipo)
│       GBargraph (Grove) Bargraph
│       (Grove) LCD1602
│       (Adrafruit) NEOPIXEL 
│       (Grove) OLED096
│
├───Sensor
|       BME280 (Various sources, I2C connection)
│       (Grove) DHT11
|       (Grove) DHTXX (Is an update of DHT11)
│       Simulator
|       (Grove) UltrasonicRanger
│
└───DeviceInput
        (Grove) Switch (new)
	Pico (74Hc165) (To be tested) 8/16 Bit Parallel In Serial Out (To micro)
Input Param: 0
OK:DeviceInput Cmds:I_getCmds,I_getDevices,I_getPins,I_setupDefault,I_setupGeneral,i__getValueRange,i_readByteValue,i_readWordValue,i_PollBit,i_Getnumbits,i_GetInstanceValueRange,i_GetInputCapab
Get next command....Is connected.
4-F5 0 1 0 
0
=================
cmd:F5 pin:0 param:1 other:0 
Input Param: 1
Get next command....Is connected.
4-F5 1 2 1 
1
=================
cmd:F5 pin:1 param:2 other:1 
Input Param: 2
DeviceInput index:1
DeviceInput name:PISO74HC165
Input pinout:Pin 16 (default), 16 to 21
Get next command.ar
```

The files in this repository are those from the src folder from the Softata Sketch in the Softa-ata repository _( see below)_  plus some from the root of the sketch folder. The Soft-ata repsository needs to be modified so as remove the src folder from this Softata folder plus those extra files, and for the softatta sketvch there to to reference this repository.

> Nb: Some device type classes such as Serial have been left in the top level code at this stage.

## Target Device
The top level code Softa-ta/Softata targets a RPi Pico W. using the [PhilHower BSP](https://github.com/earlephilhower/arduino-pico). This code should work with other Arduinodevices except the inclusion of the Watchdog timer mechanism.
Pico 2W wil be tested in the near future.

## Sample Code
There is one example sketch thus far in the examples folder, interrogate. This will run on a RPi Pico W configured for Arduino and return information about supported devices without actually needing any to be connected.

## Usage
Download the zip file, ``` [Code]-Clone-Download Zip```, green button top right when at root of the repository in GitHub.
Create a new sketch then Sketch->Include Library->Add zip file and browse to the downloaded zip file.
The required includes are as per the ```interrogate``` sketch:

```cpp
#include <softatadevice.h>
#include <softataDevice_sensor.h>
#include <SoftataDevice_environsensors.h>
#include <SoftataDevice_display.h>
#include <SoftataDevice_actuator.h>
```

---------------

## Refactoring  

***Restatement:*** A refactoring of the repository [djaus2/Soft-ata](https://gitshub.com/Softata) such that ```<repo>/code/Softata/src``` directory is separated to here.

This refactored version of that folder so that it is a separate Arduino library.

Previously this folder sat below the root of the Arduino softata sketch folder. It is confiured as a hierachy of classes so that a device class inherits methods from defined in the parent and so that all classes antecendant from the same parent have the same methods, but with device specific implementations. For example, all displays implement the ```Clear()``` method. Also, all displays implement a ```Misc()``` method that has methods specific to the display type. For example, the bargraph has a misc.floww() method that turns on every odd segenment. 

Methods that do not return a value (such as with a sensor read), return a tristate enum value which is normally ```_ok```. If there is an error in the method, ```_nok``` is returned. If a method is not implemneted then ```notimplemneted``` is returned which at a higher level is meant to be interpretteed is OK but can be used otherwise. ```_nan_``` is alos a return option for data reads.
one 

----------------

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



