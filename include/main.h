#ifndef MAIN_H_
#define MAIN_H_

#include "global_vars.h"
#include "connection_handler.h"
#include "config_handler.h"
#include "event_handler.h"
#include <FlashStorage_SAMD.h>

void commitFlash();
int readFlash(int index);
void writeFlash(int index, int value);

#endif