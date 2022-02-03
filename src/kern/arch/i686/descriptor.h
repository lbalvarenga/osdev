#ifndef I686_DESCRIPTOR_H
#define I686_DESCRIPTOR_H

#include <stdint.h>

#define GDT_FLAG_GRAN 0x80 // Granularity
#define GDT_FLAG_SIZE 0x40 // 32-bit segment mode
#define GDT_FLAG_LONG 0x20 // Long mode

#define GDT_SEG_PRESENT 0x80 // Is present
#define GDT_SEG_RING_0  0x00 // Operates at ring 0
#define GDT_SEG_NOT_TSS 0x10 // Is not TSS
#define GDT_SEG_EXEC    0x08 // Is executable
#define GDT_SEG_DIR_CON 0x04 // Direction/Conforming bit
#define GDT_SEG_RW      0x02 // Readable/Writable

// Generic descriptor descriptor for GDT and IDT (XDT)
typedef struct __attribute__((packed)) {
  uint16_t size;   // Size of table
  uint32_t offset; // Location of table start
} XDT_DESC;

typedef struct __attribute__((packed)) {
  uint16_t lim_0;  // Maximum addressable unit
  uint16_t bas_0;  // Segment start
  uint8_t  bas_1;
  uint8_t  access; // Segment access configuration
  uint8_t  flagsl; // Flags (4MSB) + Limit (4LSB)
  uint8_t  bas_2;
} TABLE_GDT;

void gdt_entry(TABLE_GDT** entry, uint32_t lim, uint32_t bas,
               uint16_t flags, uint8_t access);

// Returns the address of the end of descriptor
XDT_DESC* register_gdt(TABLE_GDT* offset, uint32_t base);

typedef struct __attribute__((packed)) {
  uint16_t off_0;    // ISR Entrypoint
  uint16_t selector; // Must point to valid code segment
  uint8_t  reserved; // Unused
  uint8_t  flags;    // Present, Privilege, 0, Type
  uint16_t off_1;
} TABLE_IDT;

void idt_entry(TABLE_IDT** entry, uint32_t isr_addr,
                     uint16_t seg, uint16_t flags);

// Returns the address of the end of descriptor
XDT_DESC* register_idt(TABLE_IDT* offset, uint32_t base);

#endif