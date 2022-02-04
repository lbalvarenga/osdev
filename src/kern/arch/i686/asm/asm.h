#ifndef I686_ASM_H
#define I686_ASM_H

#include <stdint.h>

// Port I/O

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
#define io_wait() outb(0x80, 0x00)

// Instructions

#define cli()      __asm__("cli")
#define sti()      __asm__("sti")
#define intr(val)  __asm__("int %0"  :: "N"(val))
#define lgdt(desc) __asm__("lgdt %0" :: "m"(*desc))
#define lidt(desc) __asm__("lidt %0" :: "m"(*desc))

// Utilities

void flush_segrs(uint16_t new_seg);

#endif
