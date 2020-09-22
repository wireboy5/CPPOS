C_SOURCES = $(wildcard \
	kernel/*.cpp \
	lib/**/*.cpp \
	modules/*.cpp \
	modules/**/*.cpp \
	modules/pci/*.cpp \
)

HEADERS = $(wildcard \
	kernel/*.h \
	lib/**/*.h \
	modules/*.h \
	modules/**/*.h \
	modules/pci/*.h \
)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.cpp=.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
CXX = /usr/local/i386elfgcc/bin/i386-elf-g++
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
# -g: Use debugging symbols in gcc
CFLAGS = -ffreestanding -Wall -Wextra -fno-exceptions -m32 -I ./

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os-image.bin
	qemu-system-i386 -fda os-image.bin -nographic

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@
%.o: %.cpp ${HEADERS}
	${CXX} ${CFLAGS} -c $< -o $@


%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	find . -type f -name '*.o' -delete