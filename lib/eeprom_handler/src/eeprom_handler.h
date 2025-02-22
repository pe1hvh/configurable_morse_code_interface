#ifndef EEPROM_HANDLER_H_
#define EEPROM_HANDLER_H_

void commitFlash();
int readFlash(int index);
void writeFlash(int index, int value);

#endif