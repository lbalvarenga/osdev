#ifndef I686_ISR_H
#define I686_ISR_H

#include "arch/i686/descriptor.h"

#define ISR_RING_0(i) idt_entry(idt, i, (uint32_t) &irq_handler_##i, code_seg, \
                      IDT_ENTRY_PRESENT | IDT_GATE_INT32 | IDT_ENTRY_RING_0)

// Returns end of IDT entries
IDT_TABLE* register_isrs(IDT_TABLE* idt, uintptr_t code_seg);

// Fallback handler
extern void irq_handler_0xFF();

extern void irq_handler_0x0A();

#endif
