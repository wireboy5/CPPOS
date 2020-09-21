#ifndef OP_H
#define OP_H

#include "mem.h"

void *operator new(size_t size);

void *operator new[](size_t size);

void operator delete(void *p);

void operator delete[](void *p);
uint16_t changeEndianness16(uint16_t val);
uint32_t changeEndianness32(uint32_t val);
#endif