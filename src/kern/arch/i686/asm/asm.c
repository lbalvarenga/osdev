#include "asm.h"

#include <stdint.h>

uint8_t inb(uint16_t port) {
  uint8_t data;
  __asm__("inb %1, %0" : "=a"(data) : "Nd"(port));
  return data;
}

void outb(uint16_t port, uint8_t data) {
  __asm__("outb %0, %1" :: "a"(data), "Nd"(port));
}

void flush_segrs(uint16_t new_seg) {
  __asm__("mov %0,   %%ax\n\t"
          "mov %%ax, %%ds\n\t"
          "mov %%ax, %%ss\n\t"
          "mov %%ax, %%es\n\t"
          "mov %%ax, %%fs\n\t"
          "mov %%ax, %%gs\n\t"
          :: "a"(new_seg));
}
