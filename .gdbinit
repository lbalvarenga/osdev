target remote :1234
aliases add 10i  "x/10i  $pc"
aliases add 20i  "x/20i  $pc"
aliases add 100i "x/100i $pc"
aliases add hp   "hexdump byte 0x100000"
aliases add hdp  "hexdump byte $pc"
aliases add cn   "target remote :1234"

pi reset_architecture("x86")

b *0x10000
c
