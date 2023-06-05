// #if defined(__linux__)
//     #error "voce nao esta usando um compilador cruzado (cross-compiler)"
// #endif
 
// #if !defined(__i386__)
//     #error "esse codigo deve ser compilado com um compilador ix86-elf"
// #endif

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../inc/string.h"
#include "../inc/vga/vga.h"
#include "../inc/debug/logs/logs.h"
#include "arch/i386/gdt/gdt.h"
#include "arch/i386/idt/idt.h"
#include "arch/i386/interrupts/isr.h"
#include "drivers/keyboard/kb.h"
#include "kernel.h"

void kernel_entry(void) {
    /*----------------- preparativos antes de inicializar o kernel -----------------*/

    // inicializando o buffer de texto linar (modo vga)
    log_info("inicializando buffer de texto no modo VGA\n");
    // no modo VGA 3, o endereço físico para o buffer de texto é 0xb8000
    vga_initialize(0xb8000);

    // inicializando e configurando a GDT
    log_info("inicializando GDT\n");
    init_gdt();
    
    // inicializando e configurando a IDT
    log_info("inicializando IDT\n");
    init_idt();

    // habilitar instruções
    log_info("INSTRUCAO: sti\n");
    __asm__ __volatile__("sti\n\t");
    
    // mapear um handler para a interrupção int 33 (interrupção do teclado)
    log_info("mapeando interrupcao: 33 | inicializar teclado...\n");
    map_interrupt_handler(33, keyboard_handler);

    /*----------------- inicializar o kernel ---------------------------------------*/
    
    vga_print(VGA_COL_WHITE, VGA_COL_BLACK, "creditos: https://github.com/joao-g33/\n\n");
    
    // ATENÇÃO: isso causa um kernel panic
    __asm__ __volatile__("int $0\n\t");

    // executar a interrupção int 33 (incia o teclado)
    __asm__ __volatile__("int $33\n\t");

    // loop infinito ao fim da execução do kernel
    for(;;) { 
        __asm__ __volatile__("hlt\n\t"); 
    }
}
