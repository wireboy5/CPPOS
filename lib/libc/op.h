#ifndef OP_H
#define OP_H

#include "mem.h"

void *operator new(size_t size);

void *operator new[](size_t size);

void operator delete(void *p);

void operator delete[](void *p);
#endif