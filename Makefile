.PHONY: clean

GCC  = gcc -m32
NASM = nasm

BUILDDIR = build
SRCDIR   = src

OBJFILES = \
		$(BUILDDIR)/obj/boot.o $(BUILDDIR)/obj/string.o $(BUILDDIR)/obj/vga.o $(BUILDDIR)/obj/memory.o \
		$(BUILDDIR)/obj/stdlib.o $(BUILDDIR)/obj/io.o $(BUILDDIR)/obj/logs.o $(BUILDDIR)/obj/gdt_idt_asm.o \
		$(BUILDDIR)/obj/interrupts.o $(BUILDDIR)/obj/gdt.o $(BUILDDIR)/obj/idt.o $(BUILDDIR)/obj/isr.o \
		$(BUILDDIR)/obj/panic.o $(BUILDDIR)/obj/kb.o $(BUILDDIR)/obj/kernel.o		 

CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -Wno-unused-variable

define log_action
@echo "\033[92m++++++++++"${1}"++++++++++\033[0m"
endef

define log_info
@echo "[INFO]:\033[92m "${1}"\033[0m"
endef

all: 
	$(call log_action, "CRIANDO DIRETÓRIOS DE MONTAGEM")
	mkdir -p $(BUILDDIR)/
	mkdir -p $(BUILDDIR)/iso/
	mkdir -p $(BUILDDIR)/bin/
	mkdir -p $(BUILDDIR)/obj/

	$(call log_action, "COMPILANDO DEPENDENCIAS")
	$(NASM) -f elf32 $(SRCDIR)/boot/boot.asm -o $(BUILDDIR)/obj/boot.o
	
	$(GCC) -c $(SRCDIR)/inc/string.c -o $(BUILDDIR)/obj/string.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/vga/vga.c -o $(BUILDDIR)/obj/vga.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/memory/memory.c -o $(BUILDDIR)/obj/memory.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/stdlib/stdlib.c -o $(BUILDDIR)/obj/stdlib.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/IO/io.c -o $(BUILDDIR)/obj/io.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/debug/logs/logs.c -o $(BUILDDIR)/obj/logs.o $(CFLAGS)

	$(NASM) -f elf32 $(SRCDIR)/kernel/arch/i386/gdt_idt.asm -o $(BUILDDIR)/obj/gdt_idt_asm.o
	$(NASM) -f elf32 $(SRCDIR)/kernel/arch/i386/interrupts/interrupts.asm -o $(BUILDDIR)/obj/interrupts.o

	$(GCC) -c $(SRCDIR)/kernel/arch/i386/gdt/gdt.c -o $(BUILDDIR)/obj/gdt.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/kernel/arch/i386/idt/idt.c -o $(BUILDDIR)/obj/idt.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/kernel/arch/i386/interrupts/isr.c -o $(BUILDDIR)/obj/isr.o $(CFLAGS)
	
	$(GCC) -c $(SRCDIR)/kernel/panic/panic.c -o $(BUILDDIR)/obj/panic.o $(CFLAGS)

	$(GCC) -c $(SRCDIR)/kernel/drivers/keyboard/kb.c -o $(BUILDDIR)/obj/kb.o $(CFLAGS)

	$(GCC) -c $(SRCDIR)/kernel/kernel.c -o $(BUILDDIR)/obj/kernel.o $(CFLAGS)
	
	$(call log_action, "GERANDO EXECUTAVEL FINAL")
	$(GCC) -T link.ld -o $(BUILDDIR)/bin/os.bin -ffreestanding -nostdlib $(OBJFILES)

	$(call log_action, "GERANDO AQUIVO ISO")
	mkdir -p ./src/boot/isodir/boot/grub
	cp ./build/bin/os.bin ./src/boot/isodir/boot/os.bin
	cp ./src/boot/grub.cfg ./src/boot/isodir/boot/grub/grub.cfg

	grub-mkrescue -o ./build/iso/os.iso ./src/boot/isodir
	
	$(call log_info, "pronto")


clean:
	$(call log_action, "LIMPANDO DIRETÓRIOS")
	rm -f $(BUILDDIR)/iso/*.iso
	rm -f $(BUILDDIR)/bin/*.bin
	rm -f $(BUILDDIR)/obj/*.o
	rm -rf ./boot/isodir/
