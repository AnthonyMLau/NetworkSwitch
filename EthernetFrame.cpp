#include "EthernetFrame.h"

EthernetFrame::EthernetFrame(){

}

bool EthernetFrame::VlanTagExists(){
    return (etherTypeOrLength == VLAN_802_1Q) || (etherTypeOrLength == VLAN_802_1AD);
}

bool EthernetFrame::IsIPv6(){
    return etherTypeOrLength == IPv6;
}