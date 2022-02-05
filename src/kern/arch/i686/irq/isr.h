#ifndef I686_ISR_H
#define I686_ISR_H

#include "arch/i686/descriptor.h"

#define ISR_RING_0(i) idt_entry(idt, i, (uint32_t) &irq_handler_##i, code_seg, \
                      IDT_ENTRY_PRESENT | IDT_GATE_INT32 | IDT_ENTRY_RING_0)

// Returns end of IDT entries
IDT_TABLE* register_isrs(IDT_TABLE* idt, uintptr_t code_seg);

// Fallback handler
extern void irq_handler_0xFF();

// Reserved Exceptions and Interrupts 0x00..0x1F
extern void irq_handler_0x00(); // [FAULT]      Divide-by-zero Error
extern void irq_handler_0x01(); // [FAULT/TRAP] Debug
extern void irq_handler_0x02(); // [INTERRUPT]  Non-maskable Interrupt
extern void irq_handler_0x03(); // [TRAP]       Breakpoint
extern void irq_handler_0x04(); // [TRAP]       Overflow
extern void irq_handler_0x05(); // [FAULT]      Bound Range Exceeded
extern void irq_handler_0x06(); // [FAULT]      Invalid Opcode
extern void irq_handler_0x07(); // [FAULT]      Device Not Available
extern void irq_handler_0x08(); // [ABORT]      Double Fault
                                //              Deprecated
extern void irq_handler_0x0A(); // [FAULT]      Invalid TSS
extern void irq_handler_0x0B(); // [FAULT]      Segment Not Present
extern void irq_handler_0x0C(); // [FAULT]      Stack-Segment Fault
extern void irq_handler_0x0D(); // [FAULT]      General Protection Fault
extern void irq_handler_0x0E(); // [FAULT]      Page Fault

// ISA Interrupts (Remapped from 0x00 to 0x20)
extern void irq_handler_0x20(); // Programmable Interrupt Timer
extern void irq_handler_0x21(); // Keyboard
extern void irq_handler_0x28(); // CMOS real-time clock
extern void irq_handler_0x32(); // PS2 Mouse

#endif
