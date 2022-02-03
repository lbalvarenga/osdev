#include "stdio.h"

// TODO: make this more flexible
#include "drv/gfx/vga.h"
#include "std/stdlib.h"
#include "std/string.h"

#include <stdint.h>
#include <stdarg.h>

static void handle_format(char dest[static 128], char mod, va_list* args) {
  switch (mod) {
    case 'x':
      strncpy(dest, "0x", 2); dest += 2;
      itoa(dest, (uint32_t) va_arg(*args, uint32_t), 16);
      break;

    case 'i':
    case 'd':
      itoa(dest, (int32_t) va_arg(*args, int32_t), 10);
      break;

    case 's':
      strncpy(dest, (char* ) va_arg(*args, char*), 128);
      break;
    
    case 'c':
      dest[0] = (char) va_arg(*args, int);
      dest[1] = '\0';
      break;

    default:
      strncpy(dest, "Not implemented", 16);
      break;
  }
}

void kprintf(char* format, ...) {
  va_list args;
  va_start(args, format);

  char buf[128];

  for (int i = 0; format[i] != '\0'; ++i) {
    if (format[i] == '%') {
      i++; handle_format(buf, format[i], &args);
      for (int j = 0; buf[j] != '\0'; ++j) {
        vga_write(buf[j]);
      }
    }
    else {
      vga_write(format[i]);
    }
  }

  va_end(args);
}

#undef BUF_SZ