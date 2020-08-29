#ifndef MEM_H
#define MEM_H
#include <stdint.h>
#include <stddef.h>

#define KERNEL_START_POINT 0x10000

namespace mem {



struct block {
    uint8_t state;
    uint32_t size;
    uint32_t next;
};

void memcpy(uint8_t *source, uint8_t *dest, int nbytes);
void memset(uint8_t *dest, uint8_t val, uint32_t len);


uint32_t createBlock(char *data);



} // namespace mem
#endif