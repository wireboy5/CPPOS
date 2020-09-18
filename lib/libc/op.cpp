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