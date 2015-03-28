#include <avr/eeprom.h>


inline void store_id(char id){
eeprom_update_byte((uint8_t*)0, (uint8_t)id);
}

//void read_id(){
//EEPROM.read(0);
//}
//

