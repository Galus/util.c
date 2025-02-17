#ifndef STR_H 
#define STR_H

#include <stddef.h> // Include stddef.h for size_t

int* get_array_from_csv_int(char* str, int* length);
size_t len_m(char *str);
void strncpy_m(char *src, char *dest, int start, int length);
void substr_m(char *src, char *dest, int start, int length);

#endif // STR_H
