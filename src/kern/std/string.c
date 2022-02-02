#include "string.h"

#include <stdint.h>

uint32_t strncpy(char* dest, char* source, uint32_t n) {
  uint32_t i;
  for (i = 0; *source != '\0' && i < n; ++i) {
    *dest++ = *source++;
  }

  return i;
}