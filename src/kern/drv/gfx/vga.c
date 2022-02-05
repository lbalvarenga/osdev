#include "vga.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

// TODO: split some functionality into a framebuffer interface
// eg newlines and scrolling
void vga_write(uint8_t data, uint8_t color) {
  volatile char* video = (volatile char* ) VGA_VIDEO_MEM;
  int pos = vga_get_cursor();
  if (pos >= VGA_RES_X * VGA_RES_Y) pos = 0;

  // TODO: detect whether on text or graphical mode

  video += pos * 2;

  *video++ = data;
  *video++ = color;

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
