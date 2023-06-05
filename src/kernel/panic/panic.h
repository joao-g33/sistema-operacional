#ifndef PANIC_H
#define PANIC_H

#include <stddef.h>
#include <stdint.h>

#define KERNEL_PANIC_DEFAULT_MSG "++++++++++++panic++++++++++++"

/// @brief função ativada na ocorrencia de um kernel panic
/// @param str mensagem informando a razão do kernel panic
void panic(const char *str);

#endif //PANIC_H