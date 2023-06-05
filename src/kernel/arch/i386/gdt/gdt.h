#ifndef GDT_H
#define GDT_H

#include <stddef.h>
#include <stdint.h>

struct gdt_entry_struct {
    uint16_t limit_low;          // 16 bits inferiores dao limite
    uint16_t base_low;           // 16 bits inferiores da base
    uint8_t base_middle;         // proximos 8 bits da base
    uint8_t access;              // flags de acesso,determina o nivel de privilegio do segmento 
    uint8_t granularity;
    uint8_t base_high;           // ultimos 8 bits da base
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry;

struct gdt_ptr_struct {
    uint16_t limit;             
    unsigned int base;                 // endereço da primeira entrada GDT
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr;

/// @brief inicia a GDT
void init_gdt();

/// carrega a GDT com um tamanho especifico
extern void gdt_set(int);

/// @brief define um valor de entrada na GDT
/// @param num index na GDT
/// @param base base
/// @param limit limite
/// @param access byte de acesso 
/// @param gran bit de granularidade
void gdt_set_entry(int num, unsigned int base, unsigned int limit, uint8_t access, uint8_t gran);

#endif //GDT_H