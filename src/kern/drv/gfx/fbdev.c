#include "fbdev.h"
#include "drv/gfx/vga.h"

#include <stdint.h>

void fb_init() {
  fb_clear(0x8F);
  vga_set_cursor(0);
}

void fb_write(uint8_t data) {
  uint16_t pos = vga_get_cursor();

  if (pos > FB_RES_X * (FB_RES_Y) - 1) {
    volatile uint8_t* video = (volatile uint8_t* ) FB_VIDEO_MEM;
    for (int i = 0; i < 2 * (FB_RES_X * (FB_RES_Y - 1)); i += 2) {
      video[i]     = video[i     + FB_RES_X * 2];
      video[i + 1] = video[i + 1 + FB_RES_X * 2];
    }
    vga_set_cursor(FB_RES_X * (FB_RES_Y - 1));
  }

  switch (data) {
    case '\n':
      vga_set_cursor(pos + VGA_RES_X - pos % VGA_RES_X);
      break;

    default:
      vga_write(data, 0xcF);
  }
}

// TODO: detect video mode
void fb_clear(uint8_t color) {
  for (int i = 0; i < VGA_RES_X * VGA_RES_Y; ++i) {
    vga_write(0x20, color); 
  }
}
