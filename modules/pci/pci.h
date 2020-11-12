#ifndef PCI_H
#define PCI_H
#include <stdint.h>
#include <lib/libc/vector.hpp>
#include <lib/cpu/io.h>
#include <lib/cpu/arch.h>
#include <modules/screen/screen.h>
#include <lib/libc/string.h>
#include <lib/libc/map.hpp>
namespace PCI {

class PCIHeader0 {
public:
    uint32_t BAR0;
    uint32_t BAR1;
    uint32_t BAR3;
    uint32_t BAR4;
    uint32_t BAR5;
    uint32_t cardbusCISPointer;
    uint16_t subsystemID, subsystemVendorID;
    uint32_t expansionROMBaseAddress;
    uint16_t reserved0; uint8_t reserved1, capabilitiesPointer;
    uint32_t reserved3;
    uint8_t maxLatency, minGrant, interruptPIN, interruptLine;
    void load(uint8_t bus, uint8_t slot,uint8_t function);
};
class PCIHeader1 {
public:
    uint32_t BAR0;
    uint32_t BAR1;
    uint8_t secondaryLatencyTimer, subordinateBusNumber, secondaryBusNumber, primaryBusNumber;
    uint16_t secondaryStatus; uint8_t IOLimit, IOBase;
    uint16_t memoryLimit, memoryBase;
    uint16_t prefetchableMemoryLimit, prefetchableMemoryBase;
    uint32_t prefetchableBaseUpper32Bits;
    uint32_t prefetchableLimitUpper32Bits;
    uint16_t IOLimitUpper16Bits, IOBaseUpper16Bits;
    uint16_t reserved0; uint8_t reserved1; uint8_t capabilityPointer;
    uint32_t expansionROMBaseAddress;
    uint16_t bridgeControl; uint8_t interruptPIN, intertuptLine;
    void load(uint8_t bus, uint8_t slot,uint8_t function);
};
class PCIHeader2 {
public:
    uint32_t cardBusSockORExCaBaseAddress;
    uint16_t secondaryStatus; uint8_t reserved0, offsetOfCapabilitiesList;
    uint8_t cardBusLatencyTimer, subordinateBusNumber, cardBusBusNumber, PCIBusNumber;
    uint32_t memoryBaseAddress0;
    uint32_t memoryLimit0;
    uint32_t memoryBaseAddress1;
    uint32_t memoryLimit1;
    uint32_t IOBaseAddress0;
    uint32_t IOLimit0;
    uint32_t IOBaseAddress1;
    uint32_t IOLimit1;
    uint16_t bridgeControl; uint8_t interruptPIN, interruptLine;
    uint16_t subsystemVendorID, subsystemDeviceID;
    uint32_t PCCardLegacyModeBaseAddress;
    
    void load(uint8_t bus, uint8_t slot,uint8_t function);
};
class PCIDevice {
public:
    uint8_t bus;
    uint8_t slot;
    uint16_t deviceID;
    uint16_t vendorID;
    uint16_t status;
    uint16_t command;
    uint16_t classCode;
    uint16_t subclass;
    uint16_t progIF;
    uint16_t RevisionID;
    uint8_t BIST;
    uint8_t headerType;
    uint8_t latencyTimer;
    uint8_t cacheLineSize;
    PCIHeader0 header0;
    void prettyPrint(int indent = 4);
};



uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);


// Check if the device supports provided function
bool checkFunction(uint8_t bus, uint8_t slot, uint8_t function);

PCIDevice getDevice(uint8_t bus, uint8_t slot, uint8_t function);

}



#endif