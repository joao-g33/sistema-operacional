#ifndef STRING_H
#define STRING_H

#include <stddef.h>

/// @brief determina o tamanho de uma string sem o caracter finalizador
/// @param str string
/// @return tamanho da string em bytes
size_t strlen(const char *str); 

/// @brief concatena 2 strings
/// @param dest string de destino
/// @param src string a ser concatenada em dest
/// @return string concatenada
char *strcat(char *dest, const char *src); 

#endif //STRING_H