#include "vga.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

// TODO: Implement mode checking
#define VGA_MODE  0x03
#define VGA_RES_X 80
#define VGA_RES_Y 25

#define VGA_REG_CTRL 0x03D4
#define VGA_REG_DATA 0x03D5

void vga_write(uint8_t data) {
  volatile char* video = (volatile char* ) 0xB8000;
  int pos = vga_get_cursor();
  video += pos * 2;

  switch (data) {
    case '\n':
      vga_set_cursor(pos + VGA_RES_X - pos % VGA_RES_X);
      return;
  }

  *video++ = data;
  *video++ = 0x07; // Light gray

  vga_set_cursor(++pos);
}

uint16_t vga_get_cursor() {
  uint16_t pos = 0;
  outb(VGA_REG_CTRL, 0x0F);
  pos |= inb(VGA_REG_DATA);
  outb(VGA_REG_CTRL, 0x0E);
  pos |= ((uint16_t) inb(VGA_REG_DATA)) << 8;
  return pos;
}

void vga_set_cursor(uint16_t pos) {
  outb(VGA_REG_CTRL, 0x0F);
  outb(VGA_REG_DATA, (uint8_t) (pos & 0xFF));
  outb(VGA_REG_CTRL, 0x0E);
  outb(VGA_REG_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}