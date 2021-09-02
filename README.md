# NetworkSwitch


## Encodings (wiki)[https://en.wikipedia.org/wiki/Ethernet_physical_layer]

- 100BASE-TX: 4B5B encoding with MTL-3 coded signalling (3 voltage levels) at 25MHz
    - [Fast ethernet](https://en.wikipedia.org/wiki/Fast_Ethernet), noimal rate = 100Mbits/s
    
- 10BASE-T	(2 voltage levels) 16MHz


## Dragonboard 410c setup:
- Ubuntu Core with classic
    - sudo classic
- 


## Benchmarking
- Write to /sys/class/gpio/gpio---/value using write(), which writes to the file
    - Debian: ~48 KHz => maximum bit rate = 24 kBit/sec
    - Ubuntu core: ~23 KHz => maximum bit rate = 11.5 kBit/sec
- Could probably be much faster if I can read/write to the memory mapped register 



## Useful links
https://rowelldionicio.com/mac-address-table-cisco-switches-ccnp-encor/



