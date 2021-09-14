# NetworkSwitch
This project is a software defined network switch in C++, implemented on the DragonBoard 410c with an ARM Cortex A53. 

To read and write ethernet frames, GPIO pins are used. See the benchmarking section for more details.

An ethernet frame is identified by looking for the frame preamble and start frame deliminator (SDF). This is done with a finite state machine so that bits can be streamed through.

After the ethernet frame is identified, source and destination MAC addresses can be read. These are 48-bit values which are stored as 64-bit integers for easy comparison. 

Destination MAC addresses are looked up in the switch table for the matching port number. If no entry is found in the switch table, all ports are broadcasted to. A antry is added to the switch table when a frame is sent from a port with a new source MAC address. 

Ethernet Frame:
![image](https://user-images.githubusercontent.com/39564012/133316455-5a4f18d5-9752-4065-be34-ae834dd4910c.png)


## Encodings (wiki)[https://en.wikipedia.org/wiki/Ethernet_physical_layer]

- 100BASE-TX: 4B5B encoding with MTL-3 coded signalling (3 voltage levels) at 25MHz
    - [Fast ethernet](https://en.wikipedia.org/wiki/Fast_Ethernet), noimal rate = 100Mbits/s
    
- 10BASE-T	(2 voltage levels) 16MHz


## Dragonboard 410c setup:
- Ubuntu Core with classic
    - sudo classic


## Benchmarking
- Write to /sys/class/gpio/gpio---/value using write(), which writes to the file
    - Debian: ~48 KHz => maximum bit rate = 24 kBit/sec
    - Ubuntu core: ~23 KHz => maximum bit rate = 11.5 kBit/sec
- Could probably be much faster if I can read/write to the memory mapped register 

## TODO:
- Make an output buffer in case data out/write speed is not sufficient for data coming in: eg. multiple ports sending to a single port


## Useful links & References
https://rowelldionicio.com/mac-address-table-cisco-switches-ccnp-encor/
https://en.wikipedia.org/wiki/Ethernet_frame



