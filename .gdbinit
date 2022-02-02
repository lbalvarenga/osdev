target remote :1234
aliases add 10i "x/10i $pc"
aliases add 20i "x/20i $pc"
aliases add hp  "hexdump byte"
aliases add hdp "hexdump byte $pc"

b *0x10000
c