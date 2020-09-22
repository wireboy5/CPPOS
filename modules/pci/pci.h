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


class PCIDevice {
public:
    uint8_t bus;
    uint8_t slot;
    uint16_t deviceID;
    uint16_t vendorID;
    uint16_t status;
    uint16_t command;
    uint8_t classCode;
    uint8_t subclass;
    uint8_t progIF;
    uint8_t RevisionID;
    uint8_t BIST;
    uint8_t headerType;
    uint8_t latencyTimer;
    uint8_t cacheLineSize;
    void prettyPrint();
};


uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);



// Check if the device supports provided function
bool checkFunction(uint8_t bus, uint8_t slot, uint8_t function);

PCIDevice getDevice(uint8_t bus, uint8_t slot, uint8_t function);
}



#endif