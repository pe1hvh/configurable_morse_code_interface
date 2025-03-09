#include "eeprom_handler.h"
#include <FlashStorage_SAMD.h>

  /**/
  void commitFlash(){
    EEPROM.commit();
  }
  int readFlash(int index) {
    return EEPROM.read(index);
  }
  void writeFlash(int index, int value) {
    EEPROM.write(index, value);
  }