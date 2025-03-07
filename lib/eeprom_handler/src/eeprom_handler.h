#ifndef EEPROM_HANDLER_H_
#define EEPROM_HANDLER_H_

int readFlash(int index);
void writeFlash(int index, int value);
void commitFlash();
#endif