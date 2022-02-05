[BITS 32]

; irq_handler is for non-error-pushing exceptions and interrupts
; err_handler is for exceptions that push an error code on the stack

; TODO: this is not space efficient, even if only by some bytes
%macro irq_handler 1
  global irq_handler_%1
  extern isr_%1
  irq_handler_%1:
    pushad ; Save registers
    cld    ; Clear direction flag (for C compatibility)
    call isr_%1
    popad  ; Restore registers
    iret   ; Return from interrupt
%endmacro

%macro err_handler 1
  global irq_handler_%1
  extern isr_%1
  irq_handler_%1:
    pushad
    cld
    call isr_%1
    popad
    ; TODO: pop error code
    iret
%endmacro

; Fallback handler
irq_handler 0xFF

; Reserved Exceptions and Interrupts 0x00..0x1F
  irq_handler 0x00 ; [FAULT]      Divide-by-zero Error
  irq_handler 0x01 ; [FAULT/TRAP] Debug
  irq_handler 0x02 ; [INTERRUPT]  Non-maskable Interrupt
  irq_handler 0x03 ; [TRAP]       Breakpoint
  irq_handler 0x04 ; [TRAP]       Overflow
  irq_handler 0x05 ; [FAULT]      Bound Range Exceeded
  irq_handler 0x06 ; [FAULT]      Invalid Opcode
  irq_handler 0x07 ; [FAULT]      Device Not Available
  err_handler 0x08 ; [ABORT]      Double Fault
                   ;              Deprecated
  err_handler 0x0A ; [FAULT]      Invalid TSS
  err_handler 0x0B ; [FAULT]      Segment Not Present
  err_handler 0x0C ; [FAULT]      Stack-Segment Fault
  err_handler 0x0D ; [FAULT]      General Protection Fault
  err_handler 0x0E ; [FAULT]      Page Fault

; ISA Interrupts (Remapped from 0x00 to 0x20)
  irq_handler 0x20 ; Programmable Interrupt Timer
  irq_handler 0x21 ; Keyboard
  irq_handler 0x28 ; CMOS real-time clock
  irq_handler 0x32 ; PS2 Mouse
