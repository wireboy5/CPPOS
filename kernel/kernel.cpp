#include "kernel.h"


void kernel_main() {
    screen::clear_screen();
    screen::kprint((char *)"Hello, World!\n");
    char chr[1024] = "";
    for(int i = 0; i < 1024; i++){
        chr[i] = 0x72-32;
    }
    screen::kprint(chr);
    mem::createBlock(chr);
    screen::kprint((char *)"Hello, World!\n");
    screen::kprint((char *)"Hello, World!\n");
    screen::kprint((char *)"Hello, World!\n");
    screen::kprint((char *)"Hello, World!\n");
}

