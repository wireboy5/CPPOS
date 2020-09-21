#include "pci.h"



namespace PCI {
    
uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;
 
    /* create configuration address as per Figure 1 */
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
 
    /* write out the address */
    IO::outl(0xCF8, address);
    /* read in the data */
    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    tmp = (uint16_t)((IO::inl(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    if(arch::is_big_endian()){
        tmp = changeEndianness16(tmp);
    }
    return (tmp);
}

bool checkFunction(uint8_t bus, uint8_t slot, uint8_t function){
    uint32_t vendor = pciConfigReadWord(bus,slot,function,0);
    return vendor!=0xFFFF;
}


uint8_t getNumFunctions(uint8_t bus, uint8_t slot){
    bool done = false;
    uint8_t i;
    while(!done){
        if(checkFunction(bus,slot,i)){
            done = true;
            break;
        } else {
            i++;
        }
    }
    return i;
}


PCIDevice getDevice(uint8_t bus, uint8_t slot, uint8_t function){
    PCIDevice dev;
    
    uint32_t vendor = pciConfigReadWord(bus,slot,function,0);
    if((uint16_t) (vendor >> 16) == 0xFFFF){
        return dev;
    }
    dev.bus = bus;
    dev.slot = slot;
    dev.vendorID = vendor;
    dev.deviceID = pciConfigReadWord(bus,slot,function,2);
    
    return dev;
}

}