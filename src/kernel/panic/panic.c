#include "../../kernel/arch/i386/interrupts/isr.h"
#include "../../inc/debug/logs/logs.h"
#include "../../inc/vga/vga.h"
#include "panic.h"

void panic(const char *str) {
    // efetuar um log de kernel panic informando a razão para o seu acontecimento
    log_crit("um kernel panic ocorreu | razao: %s\n", str);

    vga_printf(VGA_COL_BLACK, VGA_COL_RED, "%s\n", KERNEL_PANIC_DEFAULT_MSG);
    vga_printf(DEFAULT_COL, "razao: %s\n", str);
    
    for(;;) { asm("hlt\n\t"); }
}
