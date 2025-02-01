#ifndef SOFTATADEVICESH
#define SOFTATADEVICESH

#include <Arduino.h>

enum Tristate {_nok=0,_ok=1,notImplemented=-1, _nan = -2, invalidParams =-3};



#define SOFTATA_VERSION "1.00"  
#define SoftataDevice_RPI_PICO_SHIELD


enum bitStuffingIndex: byte {e_cmd,e_pin,e_param,e_other,e_otherDataCount,e_data1,e_data2, e_num};
static int bitStuffing[] = {256,16,16,16,16,256,16};




#ifdef RPI_PICO_DEFAULT
#define DHT11Pin_D  13 // Whatever 0 to 26
#define UART0TX   0  // GPIO0, GPIO16, GPIO22
#define UART0RX   (UART0TX+1)
#define UART1TX   4  // GPIO4, GPIO8, GPIO12
#define UART1RX   (UART1TX+1)
// Default I2C is first listed pin
#define I2C0_SDA  4 // GPIO0, GPIO4, GPIO8, GPIO12, GPIO16, GPIO20
#define I2C0_SCL  (I2C0_SDA +1)
// Next default TBD:
#define I2C1_SDA  6 // GPIO2, GPIO6, GPIO10, GPIO14, GPIO18, GPIO26
#define I2C1_SCL  (I2C1_SDA +1)
#elif defined(SoftataDevice_RPI_PICO_SHIELD)
// Note following are fixed for the Shield
#define DHT11Pin_D  16 // or 18,20
#define UART0TX   0
#define UART0RX   (UART0TX+1)
#define UART1TX   4
#define UART1RX   (UART1TX+1)
#define I2C0_SDA  8
#define I2C0_SCL  (I2C0_SDA +1)
#define I2C1_SDA  6
#define I2C1_SCL  (I2C1_SDA +1)
#endif


// Max number of bytes in msgs from client to service here
//#define maxRecvdMsgBytes 32

#define G_DEVICETYPES C(sensor)C(display)C(actuator)C(communication)C(serial)C(deviceinput)

//Add other sensors/actuators here C bracketed, on end.
#define G_SENSORS C(DHT11)C(BME280)C(UltrasonicRanger)C(Simulator)C(DHTXX)
#define G_ACTUATORS C(SERVO)C(SIPO_74HC595)C(RELAY)C(QUADRELAYS)C(LED) //LED or other signle bit Grove devices need to be last
#define G_DISPLAYS C(OLED096)C(LCD1602)C(NEOPIXEL)C(BARGRAPH)C(GBARGRAPH)
#define G_SERIAL C(LOOPBACK)C(GPS)
#define G_DEVICEINPUTS C(GSWITCH)
// Note direct assignment of these at top of softatdevice.h
// ie Add a new device type here then #define to this wuthout the G_ prefix in that file.

//////////////////////// C O M M A N D   T Y P ES  //////////////////////////////////////////
#define ANALOG_CMDS 0xA0
#define PWM_CMDS 0xB0
#define SERVO_CMDS 0xC0
#define DIGITAL_CMDS 0xD0
#define SERIAL_CMDS 0xE0

#define SOFTATDEVICE_CMD 0xF0
#define SOFTATADEVICE_SENSOR_CMD        (SOFTATDEVICE_CMD + sensor)
#define SOFTATADEVICE_DISPLAY_CMD       (SOFTATDEVICE_CMD + display)
#define SOFTATADEVICE_ACTUATOR_CMD      (SOFTATDEVICE_CMD + actuator)
#define SOFTATADEVICE_DEVICEINPUT_CMD   (SOFTATDEVICE_CMD + deviceinput)

///////////////////////// I N P U T S /////////////////////////////////////////////////


enum DEVICEINPUTcapabilities { i_none=0, i_bit = 1 , i_readbyte = 2, i_readword = 4};

#define DEVICEINPUT_COMMANDS C(I_getCmdsCMD)C(I_getDevicesCMD)C(I_getPinsCMD)C(I_setupDefaultCMD)C(I_setupGeneralCMD)C(i__getValueRangeCMD)C(i_readByteValueCMD)C(i_readWordValueCMD)C(i_PollBitCMD)C(i_GetnumbitsCMD)C(i_GetInstanceValueRangeCMD)C(i_GetInputCapabCMD)

#ifdef RPI_PICO_DEFAULT
#define GSWITCH_PINOUT "GPIO: Pin 11 or whatever 0 to 26"
#elif defined(SoftataDevice_RPI_PICO_SHIELD)
#define GSWITCH_PINOUT "Pin 16 (default), 16 to 21"
#endif

#define DEVICEINPUT_PINOUTSC C(GSWITCH_PINOUT)
#define C(x) x,
const char * const DEVICEINPUT_PINOUTS[] = { DEVICEINPUT_PINOUTSC  };
#undef C

#define DEFAULT_GSWITCH_PIN 16

#define GSWITCH_MAX 1
#define GSWITCH_RANGE "N/A"

#define DEVICEINPUT_RANGEC C(GSWITCH_RANGE)

#define C(x) x,
const char * const DEVICEINPUT_RANGES[] = { DEVICEINPUT_RANGEC  };
#undef C

///////////////////////// A C T U A T O R S /////////////////////////////////////////////////

//enum actuatorcapabilities {a_singlebit,a_bitonly,a_writeonly,a_both};
enum actuatorcapabilities { a_none=0, a_bit = 1 , a_writebyte = 2, a_writeword = 4, a_writedouble = 8 };

#define ACTUATOR_COMMANDS C(A_getCmdsCMD)C(A_getDevicesCMD)C(A_getPinsCMD)C(A_setupDefaultCMD)C(A_setupGeneralCMD)C(a__getValueRangeCMD)C(a_writeDoubleValueCMD)C(a_writeByteValueCMD)C(a_writeWordValueCMD)C(a_SetBitStateCMD)C(a_SetBitCMD)C(a_ClearBitCMD)C(a_ToggleBitCMD)C(a_GetnumbitsCMD)C(a_GetInstanceValueRangeCMD)C(a_GetActuatorCapabCMD)

#ifdef RPI_PICO_DEFAULT
#define SERVO_PINOUT "GPIO: Pin 11 or whatever 0 to 26"
#define RELAY_PINOUT "GPIO: Pin 11 or whatever 0 to 26"
#define SIPO_74HC595_PINOUT "GPIO: Pin 11 or whatever 0 to 26. 3 pins required, DS, ST_CP and SH_CP."
#define QUADRELAYS_PINOUT "GPIO: Pins 11,12,13,14 or whatever 0 to 26. 4 pins required."
#elif defined(SoftataDevice_RPI_PICO_SHIELD)
#define SERVO_PINOUT "Pin 16 (default), 16 to 21"
#define RELAY_PINOUT "Pin 16 (default), 16 to 21 (Grove evens only)"
#define SIPO_74HC595_PINOUT "Pins 16 (DS of 74HC595-Pin14) + 20 (ST_CP of 74HC595-Pin12) + 21 (SH_CP of 74HC595-Pin11) Option set num bits"
#define QUADRELAYS_PINOUT "Pin 16 (default), 16 to 21 (Grove evens only) Option set num bits"
#endif

#define ACTUATOR_PINOUTSC C(SERVO_PINOUT)C(SIPO_74HC595_PINOUT)C(RELAY_PINOUT)C(QUADRELAYS_PINOUT)

#define C(x) x,
const char * const ACTUATOR_PINOUTS[] = { ACTUATOR_PINOUTSC  };
#undef C

#define DEFAULT_SERVO_PIN 16
#define DEFAULT_RELAY_PIN 16
#define DEFAULT_QUADRELAYS_PIN 16
#define DEFAULT_QUADRELAYS_NUM_BITS 4
#define SERVO_RANGE "0...180 Angle" 
#define SERVO_MAX 180
#define SERVO_MIN 0
#define SIPO_74HC595_MAX 255
#define RELAY_MAX 1
#define RELAY_RANGE "N/A"
#define QUADRELAYS_RANGE "1...8 bits default 4"
#define SIPO_74HC595_RANGE "0...255 8 bitz. Can do 16 too."

#define ACTUATOR_RANGEC C(SERVO_RANGE)C(SIPO_74HC595_RANGE)C(RELAY_RANGE)C(QUADRELAYS_RANGE)

#define C(x) x,
const char * const ACTUATOR_RANGES[] = { ACTUATOR_RANGEC  };
#undef C



///////////////////////// S E N S O R S /////////////////////////////////////////////////

#define SENSOR_COMMANDS C(S_getCmdsCMD)C(S_getDevicesCMD)C(S_getPinsCMD)C(S_setupDefaultCMD)C(S_setupCMD)C(s__getPropertiesCMD)C(s_readallCMD)C(s_readCMD)C(s_getTelemetry)C(s_sendTelemetryBT)C(s_sendTelemetryToIoTHub)C(s_pause_sendTelemetry)C(s_continue_sendTelemetry)C(s_stop_sendTelemetry)

// Adds about 1sec to telemtry transmit (in second core).
#define TELEMETRY_DOUBLE_FLASH_INBUILT_LED

#define DHT11_PROPERTIES "Temperature,Humidity"
#define DHTXX_PROPERTIES DHT11_PROPERTIES
#define BME280_PROPERTIES "Temperature,Pressure,Humidity"
#define URANGE_PROPERTIES "mm,cm,inches"
#define SIMULATOR_PROPERTIES "Temperature"

#define NUM_DHT11_PROPERTIES 2
#define NUM_DHTXX_PROPERTIES NUM_DHT11_PROPERTIES
#define NUM_BME280_PROPERTIES 3
#define NUM_URANGE_PROPERTIES 3
#define NUM_SIMULATOR_PROPERTIES 1

//#define BME280_I2C_ADDRESS76
#define BME280_I2C_ADDRESS77
#define BME280_ADDR        0x77  // or 0x76

//Sensor connections

#ifdef RPI_PICO_DEFAULT
#define BME280_PINOUT  "I2C0 (Pins4/5 (SDA/SCL) default): Address 0x77 (Alt 0x76). Embedded in driver though."
#define DHT11_PINOUT "OneWire: Pin 11 or whatever 0 to 26"
#define DHTXX_PINOUT DHT11_PINOUT
#define URANGE_PINOUT "Digital and PWM: Pin 11 or whatever 0 to 26"
#define SIMULATOR_PINOUT "None"
#elif defined(SoftataDevice_RPI_PICO_SHIELD)
#define BME280_PINOUT  "I2C0 (Pins8/9 (SDA/SCL - fixed) = Address 0x77 (Alt 0x76). Embedded in driver though."
#define DHT11_PINOUT  "OneWire: Pin 16 (default), 18 or 20"
#define DHTXX_PINOUT  DHT11_PINOUT
#define URANGE_PINOUT "Digital and PWM: Pin 16 (default), 18 or 20"
#define SIMULATOR_PINOUT "None"
#endif

#define DEFAULT_DHT11_PIN 16
#define DEFAULT_DHTXX_PIN DEFAULT_DHT11_PIN
#define DEFAULT_URANGE_PIN 16

#define DHTXX_MIN_TIME_BTW_READS_MS 1000;
#define DHTXX_MIN_TIME_BTW_READS_MS_INCR 250; 

#define SENSOR_PINOUTSC C(DHT11_PINOUT)C(BME280_PINOUT)C(URANGE_PINOUT)C(SIMULATOR_PINOUT)C(DHTXX_PINOUT)

#define C(x) x,
const char * const SENSOR_PINOUTS[] = { SENSOR_PINOUTSC  };
#undef C

#define SENSOR_PROPERTIESC C(DHT11_PROPERTIES)C(BME280_PROPERTIES)C(URANGE_PROPERTIES)C(SIMULATOR_PROPERTIES)C(DHTXX_PROPERTIES)

#define C(x) x,
const char * const SENSOR_PROPERTIES[] = { SENSOR_PROPERTIESC  };
#undef C

//const int NUM_SENSOR_PROPERTIES[] = 


///////////////////////// D I S P L A Y S /////////////////////////////////////////////////

#define DISPLAY_COMMANDS C(D_getCmdsCMD)C(D_getDevicesCMD)C(D_getPinsCMD)C(D_setupDefaultCMD)C(D_setupCMD)C(D_dispose)C(d__miscGetListCMD)C(d_clearCMD)C(d_backlightCMD)C(d_setCursorCMD)C(d_writestringCMD)C(d_cursor_writestringCMD)C(d_home)C(d_dummyCMD)C(d_miscCMD)

// Note: Addresses are typically defined in the device library which typically use I2C0
#define OLEDDISPLAY_ADDR   0x78
#define LCD1602LCD_V2_ADDR 0X3E
#define LCD1602RGB_V2_ADDR 0X62

#define NEOPIXEL_NUMPIXELS 8
#ifdef RPI_PICO_DEFAULT
#define NEOPIXEL_PIN 12 // Whatever 0 to 26
#elif defined(SoftataDevice_RPI_PICO_SHIELD)
#define NEOPIXEL_PIN 16 //18,20 (Grove yellow cable).. 17,19,21 (Grove white cable)
#endif

//#define maxNumDisplaySettings 4

//Display connections

#ifdef RPI_PICO_DEFAULT
#define OLED096_PINOUT  "I2C0 (Pins4/5 (SDA/SCL) default): Address 0x78. Embedded in driver though."
#define LCD1602_PINOUT  "I2C0 (Pins4/5 (SDA/SCL) default): Addresses (LCD)0X3E and (RGB)0X62. Embedded in driver though."
#define NEOPIXEL_PINOUT "OneWrire: Pin 12 // Whatever 0 to 26"
#elif defined(SoftataDevice_RPI_PICO_SHIELD)
#define OLED096_PINOUT  "I2C0 (Pins8/9 (SDA/SCL) fixed) = Address 0x78. Embedded in driver though."
#define LCD1602_PINOUT  "I2C0 (Pins8/9 (SDA/SCL) fixed) = Addresses (LCD)0X3E and (RGB)0X62. Embedded in driver though."
#define NEOPIXEL_PINOUT "OneWire: Pin 16 (default), 18 or 20 (Grove yellow cable),17 or 19 or 21 (Grove white cable)"
#define BARGRAPH_PINOUT "Pins 16 (DS of 74HC595-Pin14) + 20 (ST_CP of 74HC595-Pin12) + 21 (SH_CP of 74HC595-Pin11)"
#define GBARGRAPH_PINOUT "Pin 16 DI (Data-MY9221) + Pin 17 DCKI (Clock-MY9221)"
#endif

#define DISPLAY_PINOUTSC C(OLED096_PINOUT)C(LCD1602_PINOUT)C(NEOPIXEL_PINOUT)C(BARGRAPH_PINOUT)C(GBARGRAPH_PINOUT)

#define C(x) x,
const char * const DISPLAY_PINOUTS[] = { DISPLAY_PINOUTSC  };
#undef C




// Add Misc commands to list here, before last one.
// Implement in SoftataDevice_XXXX::Misc(int cmd, int * data, int length)

#define OLEDMiscCmdsC C(drawCircle)C(drawFrame)C(test)C(OLEDMiscCmds_MAX)
#define LCD1602MiscCmdsC C(autoscrollon)C(noautoscroll)C(blinkon)C(noblink)C(LCD1602MiscCmds_MAX)
#define NEOPIXELMiscCmdsC C(setpixelcolorOne)C(setpixelcolorAll)C(setpixelcolorOdds)C(setpixelcolorEvens)C(setBrightness)C(setNum)C(setPxl)C(NEOPIXELMiscCmds_MAX)
#define BARGRAPHMiscCmdsC C(flowodd)C(floweven)C(set_Led)C(clr_Led)C(toggle_Led)C(setLevel)C(exercise)C(allOn)C(BARGRAPHMiscCmds_MAX)
//#define CUSTOM_BARGRAPHMiscCmdsC BARGRAPHMiscCmdsC

// C(_floweven)C(_flowodd)C(_setLed)C(_clrLed)C(_toggleLed)C(_setLevel)C(_exercise)C(_allOn)C(_BARGRAPHMiscCmds_MAX)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define C(x) #x,
const char * const OLEDMiscCmdsArr[] = { OLEDMiscCmdsC  };
#undef C


#define C(x) x,
enum OLEDMiscCmds { OLEDMiscCmdsC };  
#undef C


#define C(x) #x,
const char * const LCD1602MiscCmdsArr[] = { LCD1602MiscCmdsC  };
#undef C

#define C(x) x,
enum LCD1602MiscCmds { LCD1602MiscCmdsC };
#undef C

#define C(x) #x,
const char * const NEOPIXELMiscCmdsArr[] = { NEOPIXELMiscCmdsC  };
#undef C

#define C(x) x,
enum NEOPIXELMiscCmds { NEOPIXELMiscCmdsC };
#undef C

#define C(x) #x,
const char * const BARGRAPHMiscCmdsArr[] = { BARGRAPHMiscCmdsC  };
#undef C

#define C(x) x,
enum BARGRAPHMiscCmds { BARGRAPHMiscCmdsC };
#undef C

/*
#define C(x) #x,
const char * const CUSTOM_BARGRAPHMiscCmdsArr[] = { BARGRAPHMiscCmdsC  };
#undef C

#define C(x) x,
enum CUSTOM_BARGRAPHMiscCmds { CUSTOM_BARGRAPHMiscCmdsC };
#undef C*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum numStringType {_DEC, _BIN, _HEX, _NONE};
enum range_units {mm,cm,inch};


#ifndef CALLBAKINFOH
#define CALLBAKINFOH
typedef String(*call_back)(void);


struct CallbackInfo
{
  unsigned long next;
  unsigned long period;
  int SensorIndex;
  bool isSensor; // False for blinking LED
  bool sendBT;   //Alt: IoT Hub, coming
  bool isRunning; // Can stop and continue Telemetry
  call_back back;
};
#endif

/*
int AddCallBack(CallbackInfo * info);
bool PauseTelemetrySend(int index);
bool ContinueTelemetrySend(int index);

// Following 2Do in SoftataCore2.h
bool StopTelemetrySend(int index); //Not the Stop sketch command
bool ToggleActuator(int index);
bool SetActuator(int index);
bool ResetActuator(int index);
*/

#endif
