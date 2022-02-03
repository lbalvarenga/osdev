#ifndef LIB_STDLIB_H
#define LIB_STDLIB_H

#include <stdint.h>

void itoa(char* dest, uint32_t value, uint8_t base);
void memset(char* dest, char value, uint8_t n); 

#endif