#include <avr/eeprom.h>

#define EEPROM_ADDR  0

inline void store_id(char id){
eeprom_update_byte((uint8_t*)EEPROM_ADDR, (uint8_t)id);
}

char * read_id(){
  static char ret[2];
  ret[0] = (char)eeprom_read_byte((uint8_t *)EEPROM_ADDR);
  ret[1] = 0;  
}


