


#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
#include <stddef.h>
#include "../modules/drivers/screen.h"
#include "../lib/libc/mem.h"
#include "../lib/libc/rand.h"
#include "../lib/libc/vector.hpp"
#include "../lib/cpu/arch.h"

extern "C" void kernel_main();


#endif