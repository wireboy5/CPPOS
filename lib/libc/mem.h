#ifndef MEM_H
#define MEM_H
#include <stdint.h>
#include <stddef.h>
#include "../../modules/drivers/screen.h"
#include "../../lib/libc/string.h"

#define KERNEL_START_POINT 0x10000

namespace mem {



struct block {
    uint8_t state;
    uint32_t size;
    uint32_t next;
};


// Copies memory from one address to the other.
void memcpy(uint32_t *source, uint32_t *dest, int nbytes);

// Sets memory byte at location.
void memset(uint32_t *dest, uint32_t val, uint32_t len);


// Default size of 1KB per block
const uint32_t defaultBlockSize = 0x400;


// Creates a memory block and returns the address.
// Maximum of defaultBlockSize.
uint32_t createBlock(char data[defaultBlockSize]);



} // namespace mem
#endif