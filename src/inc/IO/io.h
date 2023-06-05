#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdint.h>

/// @brief le o valor de uma porta e retorna o valor recebido nessa porta
/// @param port valor da porta
/// @return valor recebido na porta
uint8_t inportb (uint16_t port);

/// @brief escreve um valor data em uma porta 
/// @param port valor da porta
/// @param data dado a ser escrito na porta
void outportb (uint16_t port, uint8_t data);

#endif //IO_H