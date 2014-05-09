C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c,%.o,$(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(putsubst %.s,%.o,$(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm
QEMU = qemu-system-i386

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o tinykernel

.PHONY:clean
clean:
	rm $(S_OBJECTS) $(C_OBJECTS) tinykernel

.PHONY:update_image
update_image:
	scripts/mount.sh
	sudo cp tinykernel /mnt/kernel/tinykernel
	sleep 1
	scripts/umount.sh

.PHONY:mount_image
mount_image:
	scripts/mount.sh

.PHONY:umount_image
umount_image:
	scripts/umount.sh

.PHONY:qemu
qemu:
	$(QEMU) -fda floppy.img -boot a

.PHONY:debug
debug:
	$(QEMU) −S −s −fda floppy.img −boot a & sleep 1
	cgdb −x scripts/gdbinit
