#ifndef DRV_VGA_H
#define DRV_VGA_H

#include <stdint.h>

// TODO: Implement mode checking
#define VGA_MODE  0x03
#define VGA_RES_X 80
#define VGA_RES_Y 25

#define VGA_REG_CTRL 0x03D4
#define VGA_REG_DATA 0x03D5

void     vga_write(uint8_t data);
uint16_t vga_get_cursor();
void     vga_set_cursor(uint16_t pos);

#endif
