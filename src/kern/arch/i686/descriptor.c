#include "descriptor.h"
#include "arch/i686/asm/asm.h"

#include <stdint.h>

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

XDT_DESC* register_gdt(TABLE_GDT* offset, uint32_t base) {
  uint16_t size = (((uintptr_t) (offset - base)) & 0xFFFF);
  XDT_DESC* gdt_desc = (XDT_DESC* ) (base + size);

  gdt_desc->size   = (uint16_t) size - 1;
  gdt_desc->offset = base;
  lgdt(gdt_desc);

  return gdt_desc++;
}

// TODO: implement isr registration
void idt_entry(TABLE_IDT** entry, uint32_t isr_addr,
                     uint16_t seg, uint16_t flags) {
  }

// TODO: DRY
XDT_DESC* register_idt(TABLE_IDT* offset, uint32_t base) {
  uint16_t size = (((uintptr_t) (offset - base)) & 0xFFFF);
  XDT_DESC* idt_desc = (XDT_DESC* ) (base + size);

  idt_desc->size   = (uint16_t) size - 1;
  idt_desc->offset = base;
  lidt(idt_desc);

  return idt_desc++;
}