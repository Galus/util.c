#ifndef IO_H 
#define IO_H

#include <stddef.h> // Include stddef.h for size_t

char **file_to_arr(char *file_name, size_t max_file_size,
                 size_t max_rows, size_t max_cols, int *lines_rows);

#endif // IO_H
