#include <EEPROM.h>
//-------------------------------------------------------------------------------------------------------
static inline void initSettings()
{
  byte settingValue;
  byte i = 0;
  
  // If no settings in EEPROM for this version of UnoLight load defaults.
  if( EEPROM.read(NUMBER_OF_SETTINGS) != UNOLIGHT_VERSION || EEPROM.read(NUMBER_OF_SETTINGS + 1) != BETA_VERSION) 
  {
    while( i < NUMBER_OF_SETTINGS )
    {
      switch( i )
      {
        case 0: 
          settingValue = true; // gamma table
          break;      
        case 1: 
          settingValue = false; // light sensor
          break;
        case 2: 
          settingValue = 30;
          break;
        case 3: 
          settingValue = 10;
          break;
        case 4: 
          settingValue = true; // smooth
          break;
        case 5: 
          settingValue = 40;
          break;
        default:
          settingValue = 0;
      }
      EEPROM.write(i++, settingValue); 
    }
    EEPROM.write(NUMBER_OF_SETTINGS, UNOLIGHT_VERSION);
    EEPROM.write(NUMBER_OF_SETTINGS + 1, BETA_VERSION);
  }
  
  i = 0; 
  while( i < NUMBER_OF_SETTINGS )
    *(settings + i++) = EEPROM.read(i);
}
//-------------------------------------------------------------------------------------------------------
static inline boolean getUpdateSettingsCommand()
{
  if( Serial.read() == UNOLIGHT_VERSION )
  {   
    for(byte i = 0; i < NUMBER_OF_SETTINGS; i++)
    {
      byte newSetting = Serial.read();   
      if( *(settings + i) != newSetting )
      {
        *(settings + i) = newSetting;
        
#if (SAVE_UPDATED_SETTINGS_TO_EEPROM == true)
        EEPROM.write(i, newSetting); 
#endif
      }
    }
    return true;
  }
  return false;
}
//-------------------------------------------------------------------------------------------------------
