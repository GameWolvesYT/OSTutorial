#$@ target
#$< first dependency
#$^all dependencies

CC 	= gcc -m32 -fno-pie
LD 	= ld -m elf_i386
GDB = gdb

C_SRC = $(shell find . -name '*.c')
SRCDIRS = $(shell find . -name '*.c' -exec dirname {} \; | uniq)
HEADERS = $(shell find . -name '*.h')

OBJ = $(patsubst %.c,build/%.o,$(C_SRC))

all: buildrepo bin/os.bin

run: buildrepo bin/os.bin
	qemu-system-i386 -boot c bin/os.bin

debug: buildrepo bin/os.bin bin/kernel.elf
	qemu-system-i386 -s -boot c -fda bin/os.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file bin/kernel.elf"

#Kernel assemble
build/kernel.bin: build/kernel_entry.o ${OBJ} build/src/cpu/interrupts.o
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

bin/kernel.elf: build/kernel_entry.o ${OBJ} build/src/cpu/interrupts.o
	${LD} -o $@ -Ttext 0x1000 $^

build/%.o: %.c ${HEADERS}
	${CC}  -Wall -Wextra -g -ffreestanding -masm=intel -c $< -o $@

build/src/cpu/interrupts.o: src/cpu/interrupts.asm
	nasm $< -f elf -o $@ -I src/boot/

build/%.o: src/boot/%.asm
	nasm $< -f elf -o $@ -I src/boot/

build/%.bin: src/boot/%.asm
	nasm $< -f bin -o $@ -I src/boot/

bin/os.bin: build/boot.bin build/kernel.bin
	cat $^ > $@

buildrepo:
	@$(call make-repo)
	
define make-repo
for dir in $(SRCDIRS); \
do \
mkdir -p build/$$dir; \
done
endef

clean:
	rm -rf build/*
