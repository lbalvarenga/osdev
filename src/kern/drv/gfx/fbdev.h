#ifndef DRV_FBDEV_H
#define DRV_FBDEV_H

// TODO: support other drivers
#include "drv/gfx/vga.h"

#include <stdint.h>

#define FB_VIDEO_MEM VGA_VIDEO_MEM
#define FB_RES_X     VGA_RES_X
#define FB_RES_Y     VGA_RES_Y

void fb_init();
void fb_write(uint8_t data);
void fb_clear(uint8_t color);

#endif
