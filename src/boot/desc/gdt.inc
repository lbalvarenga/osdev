[BITS 16]

; Sets up basic overlapping code+data segments up to 4GiB
; The kernel should load a new gdt at some point
gdt_start:
  gdt_null:
    dw 0x0000 ; Limit 0-15
    dw 0x0000 ; Base  0-15

    db 0x00       ; Base 16-23
    db 0b00000000 ; Access Byte
    db 0b00000000 ; Flags + Limit 16-19
    db 0x00       ; Base 24-31
  
  gdt_code:
    dw 0xFFFF ; Limit 0-15
    dw 0x0000 ; Base  0-15

    db 0x00       ; Base 16-23
    db 0b10011010 ; Access Byte
    db 0b11001111 ; Flags + Limit 16-19
    db 0x00       ; Base 24-31

  gdt_data:
    dw 0xFFFF ; Limit 0-15
    dw 0x0000 ; Base  0-15

    db 0x00       ; Base 16-23
    db 0b10010010 ; Access Byte
    db 0b11001111 ; Flags + Limit 16-19
    db 0x00       ; Base 24-31
gdt_end:

gdt_desc:
  dw gdt_end - gdt_start - 1 ; Size
  dq gdt_start               ; Offset