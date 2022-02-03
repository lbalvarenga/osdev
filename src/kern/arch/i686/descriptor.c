#include "descriptor.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

// TODO: implement interrupts wrapper with asm
#include "std/stdio.h"
void inthd() {
  kprintf("INTERRUPT!");
  while(1) {}
}

// TODO: consider return struct with gdt segments
// This should be edited to reflect memory mapping needs
void setup_descriptors() {
  // TODO: place in other file and choose a proper address
  TABLE_GDT* gdt = (TABLE_GDT* ) DESCRIPTOR_BASE;
  gdt_entry(&gdt, 0, 0, 0, 0);

  uintptr_t code_seg = (uintptr_t) gdt - DESCRIPTOR_BASE;
  gdt_entry(&gdt,
  0x000FFFFF, 0x00000000,                         // Limit, Base
  GDT_FLAG_GRAN   | GDT_FLAG_SIZE  ,              // Flags
  GDT_SEG_PRESENT | GDT_SEG_RING_0 |              // Access
  GDT_SEG_NOT_TSS | GDT_SEG_EXEC   | GDT_SEG_RW); // Access

  // uintptr_t data_seg = gdt - DESCRIPTOR_BASE;
  gdt_entry(&gdt,
  0x000FFFFF, 0x00000000,             // Limit, Base
  GDT_FLAG_GRAN   | GDT_FLAG_SIZE  ,  // Flags
  GDT_SEG_PRESENT | GDT_SEG_RING_0 |  // Access
  GDT_SEG_NOT_TSS | GDT_SEG_RW     ); // Access
   
  // TODO: Consider aligning IDT
  TABLE_IDT* idt_base = (TABLE_IDT* ) register_gdt(gdt, DESCRIPTOR_BASE);

  TABLE_IDT* idt = idt_base;
  for (int i = 0; i < 256; ++i) {
    idt_entry(&idt,
    (uintptr_t) &inthd, code_seg,          // Handler, Code segment
    IDT_ENTRY_PRESENT | IDT_ENTRY_RING_0 | // Flags
    IDT_GATE_INT32);
  }
  register_idt(idt, (uint32_t) idt_base);
}

void gdt_entry(TABLE_GDT** entry, uint32_t lim, uint32_t bas,
               uint16_t flags, uint8_t access) {
  (*entry)->lim_0  = (uint16_t)   lim        & 0xFFFF;
  (*entry)->bas_0  = (uint16_t)   bas        & 0xFFFF;
  (*entry)->bas_1  = (uint8_t ) ((bas >> 16) &  0xFF);
  (*entry)->bas_2  = (uint8_t ) ((bas >>  8) &  0xFF);
  (*entry)->flagsl = flags    | ((lim >> 16) &  0x0F);
  (*entry)->access = access;
  (*entry)++;
}

XDT_DESC* register_gdt(TABLE_GDT* offset, uint32_t gdt_base) {
  uint16_t size = (uint16_t) ((uint32_t) (offset - gdt_base)) & 0xFFFF;
  XDT_DESC* gdt_desc = (XDT_DESC* ) offset;

  gdt_desc->size   = size - 1;
  gdt_desc->offset = gdt_base;
  lgdt(gdt_desc);

  return gdt_desc + 1;
}

void idt_entry(TABLE_IDT** entry, uint32_t isr_addr,
               uint16_t seg, uint8_t flags) {
    (*entry)->off_0    = (uint16_t) (isr_addr & 0xFFFF);
    (*entry)->off_1    = (uint16_t) ((isr_addr >> 16) & 0xFFFF);
    (*entry)->selector = seg;
    (*entry)->reserved = 0;
    (*entry)->flags    = flags;
    (*entry)++;
  }

// TODO: DRY
XDT_DESC* register_idt(TABLE_IDT* offset, uint32_t idt_base) {
  uint16_t size = (uint16_t) ((uint32_t) (offset - idt_base)) & 0xFFFF;
  XDT_DESC* idt_desc = (XDT_DESC* ) offset;

  idt_desc->size   = size - 1;
  idt_desc->offset = idt_base;
  lidt(idt_desc);

  return idt_desc + 1;
}
