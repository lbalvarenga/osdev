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
    
    call isr_%1

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