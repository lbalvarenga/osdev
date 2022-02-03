#include "vga.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

// TODO: split some functionality into a framebuffer interface
// eg newlines and scrolling
void vga_write(uint8_t data) {
  volatile char* video = (volatile char* ) 0xB8000;
  int pos = vga_get_cursor();
  if (pos >= VGA_RES_X * VGA_RES_Y) pos = 0;

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
