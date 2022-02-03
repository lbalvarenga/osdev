#include "descriptor.h"
#include "arch/i686/irq/isr.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

// TODO: consider return struct with gdt segments
// This should be edited to reflect memory mapping needs
void setup_descriptors() {
  // TODO: flush segment registers
  GDT_TABLE* gdt = (GDT_TABLE* ) DESCRIPTOR_BASE;
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

  IDT_TABLE* idt_base = (IDT_TABLE* ) register_gdt(gdt, DESCRIPTOR_BASE);
  // Align idt_base, since GDT Descriptor is 6 bytes long
  idt_base = (IDT_TABLE* ) ((uintptr_t) idt_base + 2);

  IDT_TABLE* idt = idt_base;
  register_isrs(&idt, code_seg);
  register_idt(idt, (uint32_t) idt_base);
}

void gdt_entry(GDT_TABLE** entry, uint32_t lim, uint32_t bas,
               uint16_t flags, uint8_t access) {
  (*entry)->lim_0  = (uint16_t)   lim        & 0xFFFF;
  (*entry)->bas_0  = (uint16_t)   bas        & 0xFFFF;
  (*entry)->bas_1  = (uint8_t ) ((bas >> 16) &  0xFF);
  (*entry)->bas_2  = (uint8_t ) ((bas >>  8) &  0xFF);
  (*entry)->flagsl = flags    | ((lim >> 16) &  0x0F);
  (*entry)->access = access;
  (*entry)++;
}

TABLE_DESC* register_gdt(GDT_TABLE* offset, uint32_t gdt_base) {
  uint16_t size = (uint16_t) ((uint32_t) (offset - gdt_base)) & 0xFFFF;
  TABLE_DESC* gdt_desc = (TABLE_DESC* ) offset;

  gdt_desc->size   = size - 1;
  gdt_desc->offset = gdt_base;
  lgdt(gdt_desc);

  return gdt_desc + 1;
}

void idt_entry(IDT_TABLE** entry, uint32_t isr_addr,
               uint16_t seg, uint8_t flags) {
    (*entry)->off_0    = (uint16_t) (isr_addr & 0xFFFF);
    (*entry)->off_1    = (uint16_t) ((isr_addr >> 16) & 0xFFFF);
    (*entry)->selector = seg;
    (*entry)->reserved = 0;
    (*entry)->flags    = flags;
    (*entry)++;
  }

// TODO: DRY
TABLE_DESC* register_idt(IDT_TABLE* offset, uint32_t idt_base) {
  uint16_t size = (uint16_t) ((uint32_t) (offset - idt_base)) & 0xFFFF;
  TABLE_DESC* idt_desc = (TABLE_DESC* ) offset;

  idt_desc->size   = size - 1;
  idt_desc->offset = idt_base;
  lidt(idt_desc);

  return idt_desc + 1;
}
