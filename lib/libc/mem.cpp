#include "mem.h"


namespace mem {

void memcpy(uint32_t *source, uint32_t *dest, int nbytes){
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}
void memset(uint32_t *dest, uint32_t val, uint32_t len){
    uint32_t *temp = (uint32_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

template<unsigned int pos>
bool is_bit_set(unsigned int value){
    return value & (1 << pos);
}

/////////////////////////////////////////////////////////////////////
// Super basic malloc from os-tutorial github.
// Only allocates, does not free.
// This will be used to implement full malloc, free, 
// and realloc functions
/////////////////////////////////////////////////////////////////////
uint32_t free_mem_addr = 0x10000;

uint32_t kmalloc(uint32_t size, int align, uint32_t *phys_addr){
        /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    /* Save also the physical address */
    if (phys_addr) *phys_addr = free_mem_addr;

    uint32_t ret = free_mem_addr;
    free_mem_addr += size; /* Remember to increment the pointer */
    return ret;
}

typedef struct free_block {
    size_t size;
    struct free_block* next;
} free_block;

static free_block free_block_list_head = { 0, 0 };

// static const size_t overhead = sizeof(size_t);


void* malloc(size_t size) {
    size = (size + sizeof(free_block) + (align_to - 1)) & ~ (align_to - 1);
    free_block* block = free_block_list_head.next;
    free_block** head = &(free_block_list_head.next);
    while (block != 0) {
        if (block->size >= size) {
            *head = block->next;
            return ((char*)block) + sizeof(free_block);
        }
        head = &(block->next);
        block = block->next;
    }
    uint32_t physaddr;
    block = (free_block*)kmalloc(size,align_to,&physaddr);
    block->size = size;

    return ((char*)block) + sizeof(free_block);
}

void free(void* ptr) {
    free_block* block = (free_block*)(((char*)ptr) - sizeof(free_block ));
    block->next = free_block_list_head.next;
    free_block_list_head.next = block;
}


// Now for realloc. (Basic version: malloc+memcpy+free)

void* realloc(void* ptr, size_t size){
    char *newpos = (char*)malloc(size);
    memcpy((uint32_t*)ptr,(uint32_t*)newpos,(int)size);
    free(ptr);
    return newpos;
}


} // namespace mem