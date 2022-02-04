[BITS 32]

; TODO: implement macro for faults that push error
; code on the stack
; TODO: this is not space efficient, even if only by some bytes
%macro irq_handler 1
  global irq_handler_%1
  extern isr_%1
  irq_handler_%1:
    pushad ; Save registers
    cld    ; Clear direction flag (for C compatibility)
    
    call isr_0x00

    popad  ; Restore registers
    iret   ; Return from interrupt
  
%endmacro

; Registration

; Exceptions 0x00-0x1F
irq_handler 0x00
irq_handler 0x01
irq_handler 0x02
irq_handler 0x03
irq_handler 0x04
irq_handler 0x05
irq_handler 0x06
irq_handler 0x07
irq_handler 0x08
irq_handler 0x09
irq_handler 0x0A
irq_handler 0x0B
irq_handler 0x0C
irq_handler 0x0D
irq_handler 0x0E
irq_handler 0x0F
irq_handler 0x10
irq_handler 0x11
irq_handler 0x12
irq_handler 0x13
irq_handler 0x14
irq_handler 0x15
irq_handler 0x16
irq_handler 0x17
irq_handler 0x18
irq_handler 0x19
irq_handler 0x1A
irq_handler 0x1B
irq_handler 0x1C
irq_handler 0x1D
irq_handler 0x1E
irq_handler 0x1F
