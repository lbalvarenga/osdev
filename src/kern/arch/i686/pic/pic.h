#ifndef I686_PIC_H
#define I686_PIC_H

#include <stdint.h>

// Ports

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xA0
#define PIC_SLAVE_DATA  0xA1

// Commands
// ICW stands for Initialization Command Words

#define PIC_EOI          0x20
#define PIC_ICW1_INIT    0x10
#define PIC_SLAVE_IDENT  0x02
#define PIC_SLAVE_OFFSET 0x04
#define PIC_MODE_8086    0x01

// Registers

#define PIC_REG_REQ 0x0A // Interrupt Request Register (IRQ being requested to PIC)
#define PIC_REG_SVC 0x0B // In-Service Register        (IRQ being serviced  by CPU)



void pic_init(uint8_t off_master, uint8_t off_slave);
void pic_disable();
void pic_eoi(uint8_t irq); // End of interrupt
uint16_t pic_get_irq();

#endif
