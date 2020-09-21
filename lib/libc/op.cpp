#include "op.h"

void *operator new(size_t size)
{
    return mem::malloc(size);
}
 
void *operator new[](size_t size)
{
    return mem::malloc(size);
}
 
void operator delete(void *p)
{
    mem::free(p);
}
 
void operator delete[](void *p)
{
    mem::free(p);
}
uint16_t changeEndianness16(uint16_t val)
{
    return (val << 8) |          // left-shift always fills with zeros
          ((val >> 8) & 0x00ff); // right-shift sign-extends, so force to zero
}
uint32_t changeEndianness32(uint32_t val)
{
    return (val << 24) |
          ((val <<  8) & 0x00ff0000) |
          ((val >>  8) & 0x0000ff00) |
          ((val >> 24) & 0x000000ff);
}