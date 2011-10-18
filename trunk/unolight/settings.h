#define SAVE_UPDATED_SETTINGS_TO_EEPROM false
#define NUMBER_OF_SETTINGS 15

// Settings variables
static byte settings[NUMBER_OF_SETTINGS]; // settings values
// Pointers (read only) to settings in settings array
static boolean * const useGammaTable = &settings[0];       // If true then gamaTable from gamaTable.h is used to get leds brightnes level
static byte * const idleTimeLimit = &settings[3];          // Time (in seconds) without data transmision after which LEDs will turn off minus one second
static byte * const isSmoothEnabled = &settings[4];        // If true smoothing of color changes is enabled (usefull when new values are supplied than 16 times per second)
static byte * const smoothAmount = &settings[5];           // if isSmoothEnabled == true than smoothAmount decides how fluent color transitions will be.
