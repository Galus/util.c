#ifndef IO_H 
#define IO_H

#include <stddef.h> // Include stddef.h for size_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **file_to_arr(char *file_name, size_t max_file_size,
                 size_t max_rows, size_t max_cols, int *lines_rows);


// Dont forget to free the memory of lines after you're done with the array.
//   for (int i = 0; i < count; i++) {
//     free(lines[i]);
//   }
//   free(lines);
char **file_to_arr(char *file_name, size_t max_file_size, size_t max_rows,
                   size_t max_cols, int *lines_rows) {

  char **lines;

  printf("Called file_to_array with...\n");
  printf("file_name: %s\n", file_name);
  printf("max_file_size: %zu\n", max_file_size);
  printf("***lines: %p\n", lines);
  printf("max_rows: %zu\n", max_rows);
  printf("max_cols: %zu\n", max_cols);
  printf("lines_rows: %d\n", *lines_rows);

  printf("Allocating space for lines.\n");
  lines = malloc(sizeof(char *) * max_rows);
  if (lines == NULL) {
    perror("malloc failed");
    return NULL;
  }

  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    perror("fopen failed");
    free(lines);
    lines = NULL;
    return NULL;
  }

  char line[max_cols];
  size_t count = 0;

  /*printf("Reading file line-by-line.\n");*/
  while (fgets(line, max_cols, file) != NULL && count < max_rows) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] != '\n' && feof(file)) {
      printf("Max line length exceeded by Line %zu\n", count);
      fprintf(stderr, "Warning: Line %zu exceeds max_cols and was truncated.\n",
              count + 1);
      line[max_cols - 1] = '\0';
      len = max_cols - 1;
    }

    /*printf("Allocating space for line of length %zu\n", len);*/
    lines[count] = malloc(sizeof(char) * (strlen(line) + 1));
    if (lines[count] == NULL) {
      printf(
          "Couldnt allocate space, freeing the space for each line pointer\n");
      perror("malloc failed for lines[count]");
      for (int i = 0; i < (int)count; i++) {
        free(lines[i]);
      }
      free(lines);
      fclose(file);
      return NULL;
    }

    /*printf("Copying the line into the lines[%zu] array.\n", count);*/
    strcpy(lines[count], line);
    len = strlen(lines[count]);
    if (len > 0 && lines[count][len - 1] == '\n') {
      /*printf("Replacing the newline with a null-terminator...\n");*/
      lines[count][len - 1] = '\0';
    }
    count++;
  }

  printf("Closing file handle\n");
  fclose(file);

  printf("Modfying line_rows value to be count\n");
  *lines_rows = count;
  return lines;
}

#endif // IO_H
