#ifndef I686_DESCRIPTOR_H
#define I686_DESCRIPTOR_H

#include <stdint.h>

// TODO: should everything here be exposed?

#define DESCRIPTOR_BASE 0x100000 // Base memory address for descriptors

#define GDT_FLAG_GRAN 0x80 // Granularity
#define GDT_FLAG_SIZE 0x40 // 32-bit segment mode
#define GDT_FLAG_LONG 0x20 // Long mode

#define GDT_SEG_PRESENT 0x80 // Is present
#define GDT_SEG_RING_0  0x00 // Operates at ring 0
#define GDT_SEG_RING_1  0x20
#define GDT_SEG_RING_2  0x40
#define GDT_SEG_RING_3  0x60
#define GDT_SEG_NOT_TSS 0x10 // Is not TSS
#define GDT_SEG_EXEC    0x08 // Is executable
#define GDT_SEG_DIR_CON 0x04 // Direction/Conforming bit
#define GDT_SEG_RW      0x02 // Readable/Writable

#define IDT_ENTRY_PRESENT 0x80 // Is present
#define IDT_ENTRY_RING_0  0x00 // Operates at ring 0
#define IDT_ENTRY_RING_1  0x20
#define IDT_ENTRY_RING_2  0x40
#define IDT_ENTRY_RING_3  0x60

#define IDT_GATE_TASK  0x05 // Task gate
#define IDT_GATE_INT16 0x06 // 16-bit interrupt gate
#define IDT_GATE_TRP16 0x07 // 16-bit trap gate
#define IDT_GATE_INT32 0x0E // 32-bit interrupt gate
#define IDT_GATE_TRP32 0x0F // 32-bit trap gate

void setup_descriptors();

// Generic descriptor descriptor (tm) for GDT and IDT
typedef struct __attribute__((packed)) {
  uint16_t size;   // Size of table
  uint32_t offset; // Location of table start
} TABLE_DESC;

typedef struct __attribute__((packed)) {
  uint16_t lim_0;  // Maximum addressable unit
  uint16_t bas_0;  // Segment start
  uint8_t  bas_1;
  uint8_t  access; // Segment access configuration
  uint8_t  flagsl; // Flags (4MSB) + Limit (4LSB)
  uint8_t  bas_2;
} GDT_TABLE;

// Makes **entry point to next location
void gdt_entry(GDT_TABLE** entry, uint32_t lim, uint32_t bas,
               uint16_t flags, uint8_t access);

// Returns the address of the end of descriptor
TABLE_DESC* register_gdt(GDT_TABLE* offset, uint32_t gdt_base);

typedef struct __attribute__((packed)) {
  uint16_t off_0;    // ISR Entrypoint
  uint16_t selector; // Must point to valid code segment
  uint8_t  reserved; // Unused
  uint8_t  flags;    // Present, Privilege, 0, Type
  uint16_t off_1;
} IDT_TABLE;

// Makes **entry point to next location
void idt_entry(IDT_TABLE** entry, uint32_t isr_addr,
                     uint16_t seg, uint8_t flags);

// Returns the address of the end of descriptor
TABLE_DESC* register_idt(IDT_TABLE* offset, uint32_t idt_base);

#endif
