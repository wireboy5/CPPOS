#include "io.h"


namespace IO {


unsigned char Port::byte_in(){
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (portOp));
    return result;
}

unsigned short Port::word_in (){
    uint16_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (portOp));
    return result;
}

void Port::byte_out (uint8_t data){
    __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (portOp));
}

void Port::word_out (uint16_t data){
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (portOp));
}



uint8_t port_byte_in (uint16_t port) {
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (uint16_t port, uint8_t data) {
    __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t port_word_in (uint16_t port) {
    uint16_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (uint16_t port, uint16_t data) {
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

} // namespace IO