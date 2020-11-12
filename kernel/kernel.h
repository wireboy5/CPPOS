


#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
#include <stddef.h>
#include <modules/pci/pci.h>
#include <modules/screen/screen.h>
#include <lib/libc/mem.h>
#include <lib/libc/rand.h>
#include <lib/libc/vector.hpp>
#include <lib/cpu/arch.h>
#include <lib/libc/string.h>


extern "C" void kernel_main();


#endif