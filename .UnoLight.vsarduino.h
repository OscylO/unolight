#define __AVR_ATmega168__
extern "C" void __cxa_pure_virtual() {}
#define __cplusplus
#define __builtin_va_list int
#define __attribute__(x)
#define __inline__
#define __asm__(x)
#include "C:\Users\OscylO\Documents\arduino-1.0\libraries\EEPROM\EEPROM.h"
#include "C:\Users\OscylO\Documents\arduino-1.0\libraries\EEPROM\EEPROM.cpp"
void setup();
void loop();
static inline void disableUnusedFunctions();
static boolean inline getAmbloneCommand();
static inline void loadNewLedValues(byte numOfValues);
static inline void resetAmblone();
static inline boolean getAtmolightCommand();
static inline void initLeds();
static inline void initTimer2();
static inline void turnOffLEDs();
static inline void smooth();
static inline void showTestingPattern();
static inline void initSensors();
static byte getSensorValue( byte pin );
static boolean turnOffIfAmbientLightToBright();
static inline void updateSensorsValues();
static inline void initSerialCommunication();
static inline boolean sendInfo();
static inline boolean getCommand();
static inline word timeElapsedSinceLastCmd();
static inline void initSettings();
static inline boolean getUpdateSettingsCommand();

#include "C:\Users\OscylO\Documents\arduino-1.0\hardware\arduino\cores\arduino\WProgram.h"
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\UnoLight.ino" 
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\amblone.ino"
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\atmolight.ino"
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\leds.ino"
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\sensors.ino"
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\serialCommunication.ino"
#include "C:\Users\OscylO\Documents\OskiArduinoProjects\UnoLight\settings.ino"
