#ifndef DRV_VGA_H
#define DRV_VGA_H

#include <stdint.h>

void     vga_write(uint8_t data);
uint16_t vga_get_cursor();
void     vga_set_cursor(uint16_t pos);

#endif