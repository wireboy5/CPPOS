#include <modules/pci/pci.h>



namespace PCI {

void PCIDevice::prettyPrint(int indent){
    uint16_t vals2[] = {
        deviceID,
        vendorID,
        status,
        command
    };
    char names2[][32] = {
        "deviceID",
        "vendorID",
        "status",
        "command"
    };
    for(int i=0; i < sizeof(vals2)/sizeof(uint16_t); i++){
        char s[256] = "";
        for(int n = 0; n < indent; n++)
            screen::kprint((char *)" ");
        screen::kprint(names2[i]);
        screen::kprint((char *)" : ");
        string::hex_to_ascii(vals2[i],s);
        screen::kprint(s);
        screen::kprint((char *)"\n");
    }
    uint8_t vals[] = {
        bus,
        slot,
        classCode,
        subclass,
        progIF,
        RevisionID,
        BIST,
        headerType,
        latencyTimer,
        cacheLineSize
    };
    char names[][32] = {
        "bus",
        "slot",
        "classCode",
        "subclass",
        "progIF",
        "RevisionID",
        "BIST",
        "headerType",
        "latencyTimer",
        "cacheLineSize"
    };
    for(int i=0; i < sizeof(vals)/sizeof(uint8_t); i++){
        char s[256] = "";
        for(int n = 0; n < indent; n++)
            screen::kprint((char *)" ");
        screen::kprint(names[i]);
        screen::kprint((char *)" : ");
        string::hex_to_ascii(vals[i],s);
        screen::kprint(s);
        screen::kprint((char *)"\n");
    }
    

}




uint32_t pciConfigReadRegister (uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint32_t tmp = 0;
    reg *= 4;
    /* create configuration address as per Figure 1 */
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (reg - (reg % 4)) | ((uint32_t)0x80000000));
 
    /* write out the address */
    IO::outl(0xCF8, address);
    /* read in the data */
    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    if(arch::is_big_endian()){
        tmp = (uint32_t)(changeEndianness32(IO::inl(0xCFC)));
    } else {
        tmp = (uint32_t)(IO::inl(0xCFC));
    }
    return (tmp);
}


uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg, uint8_t offset) {
    uint32_t regRead = pciConfigReadRegister(bus,slot,func,reg);
    return (regRead >> (offset * 8))&0xFFFF;
}

uint8_t pciConfigReadByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg, uint8_t offset) {
    uint32_t regRead = pciConfigReadRegister(bus,slot,func,reg);
    return (uint8_t)((regRead >> (offset * 8))&0xFF);
}

bool checkFunction(uint8_t bus, uint8_t slot, uint8_t function){
    uint32_t vendor = pciConfigReadWord(bus,slot,function,0,0);
    return vendor!=0xFFFF;
}



uint8_t getNumFunctions(uint8_t bus, uint8_t slot){
    uint8_t i;
    while(checkFunction(bus,slot,i)) i++;
    return i;
}

PCIDevice getDevice(uint8_t bus, uint8_t slot, uint8_t function){
    PCIDevice dev;
    
    uint32_t vendor = pciConfigReadWord(bus,slot,function,0x00,0);
    if((uint16_t) (vendor >> 16) == 0xFFFF){
        return dev;
    }
    dev.bus = bus;
    dev.slot = slot;
    dev.vendorID = vendor;
    dev.deviceID = pciConfigReadWord(bus,slot,function,0x00,2);
    dev.status = pciConfigReadWord(bus,slot,function,0x01,0);
    dev.command = pciConfigReadWord(bus,slot,function,0x01,2);
    char a[10];
    string::hex_to_ascii(pciConfigReadRegister(bus,slot,function,0x02),a);
    screen::kprint(a);
    dev.classCode = pciConfigReadByte(bus,slot,function,0x02, 0x03);
    dev.subclass = pciConfigReadByte(bus,slot,function,0x02, 0x02);
    dev.progIF = pciConfigReadByte(bus,slot,function,0x02, 0x01);
    dev.RevisionID = pciConfigReadByte(bus,slot,function,0x02, 0x00);
    dev.BIST = pciConfigReadByte(bus,slot,function,0x03,0x03);
    dev.headerType = pciConfigReadByte(bus,slot,function,0x03,0x02);
    dev.latencyTimer = pciConfigReadByte(bus,slot,function,0x03,0x01);
    dev.cacheLineSize = pciConfigReadByte(bus,slot,function,0x03,0x00);
    return dev;
}




}
