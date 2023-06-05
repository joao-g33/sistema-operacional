#ifndef ISR_H
#define ISR_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t ds;                                     // seletor de segmento de dados
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // empurrados no stack pela instrução "pusha"
    uint32_t int_no, err_code;                       // numero da interrupção e código de erro    
    uint32_t eip, cs, eflags, useresp, ss;           // automaticamente empurrados pelo processador no stack
} registers;

/// @brief recebe uma porta e envia um comando para PIC
extern void EOI();

// registradores
typedef void (*isr)(registers); 

/// @brief mapeia um handler para uma dada instrução
/// @param interrupt_number numero da interrupção 
/// @param handler handler da interrupção
void map_interrupt_handler(uint32_t interrupt_number, isr handler);

/// @brief handler de rotinas de serviço de interrupções
/// @param reg registradores
void isr_handler(registers reg);

/// @brief handler de requisições de interrupções
/// @param reg registradores
void irq_handler(registers reg);

#endif //ISR_H