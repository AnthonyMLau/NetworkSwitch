#include "EthernetFrame.h"

EthernetFrame::EthernetFrame(){

}

bool EthernetFrame::VlanTagExists(){
    return (etherTypeOrLength == vlanQ) || (etherTypeOrLength == vlanAD);
}