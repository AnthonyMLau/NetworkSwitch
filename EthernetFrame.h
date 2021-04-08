#include "MACAddress.h"

#define PREAMBLE_STR "10101010 10101010 10101010 10101010 10101010 10101010 10101010"
#define PREAMBLE_BIN 0b10101010 10101010 10101010 10101010 10101010 10101010 10101010
#define SFD_STR "10101011"
#define SFD_BIN 0b10101011

#define OPTIONAL_LENGTH_BLT 1500  // = or less than -  means that that it is is size of payload in # of octets
#define OPTIONAL_ETHERTYPE_BGT 1536  // = or greater than -  means that it is EtherType

#define VLAN_802_1Q 0x8100
#define VLAN_802_1AD 0x88a8
#define ARP 0x0806 
#define IPv6 0x86DD

// 1 octet = 8 hex digits = 32 bits => 32 bit int

class EthernetFrame{
    public:
        static const int vlanQ = VLAN_802_1Q;
        static const int vlanAD = VLAN_802_1AD;

        EthernetFrame();
        ~EthernetFrame();
        void Deserialize();
        void Serialize();
        bool VlanTagExists();
        bool IsEtherType();
        


    private:
        MACAddress destination;
        MACAddress source;
        int vlanTag;
        int etherTypeOrLength;
        int * data;
        int CRC;
          
};