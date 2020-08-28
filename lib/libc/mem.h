#include <stdint.h>
#include <stddef.h>

#define KERNEL_START_POINT 0x10000

namespace mem {



void memory_copy(uint8_t *source, uint8_t *dest, int nbytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

uint32_t free_mem_addr = KERNEL_START_POINT;

uint32_t blockHeaderSize = 0x1;

uint32_t free_mem_addr = KERNEL_START_POINT;

uint32_t kmalloc(size_t, int align, uint32_t *phys_addr);

void kfree (void* ptr);

uint32_t virtualToPhysical(uint32_t virt);

uint32_t physicalToVirtual(uint32_t virt);

} // namespace mem