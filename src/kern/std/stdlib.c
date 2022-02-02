#include "stdlib.h"

#include <stdint.h>

// TODO: Standardize buffer size
void itoa(char* dest, int32_t value, uint8_t base) {
  uint32_t i = 0, j = 0;
  char temp[128] = { 0 };

  // TODO: implement unsigned 
  if (value < 0) {
    value -= 2 * value;
    dest[j] = '-'; dest++;
  }

  if (value == 0) {
    dest[0] = '0'; dest[1] = '\0';
    return;
  }

  for (i = 0; value != 0; ++i) {
    int r = value % base;
    temp[i] = (r > 9) ? r - 10 + (int) 'A' : r + (int) '0';
    value /= base; 
  }

  // temp is reversed
  for (j = 0; j < 128; ++j) {
    dest[j] = temp[i - j - 1];
  }
  
  dest[j] = '\0';
}

void memset(char* dest, char value, uint8_t n) {
  for (uint8_t i = 0; i < n; ++i) {
    dest[i] = value;
  }
}