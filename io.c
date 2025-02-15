#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 9999
#define MAX_LINES 1000

//Dont forget to free the memory of lines after you're done with the array.
//  for (int i = 0; i < line_num; i++) {
//    free(lines[i]);
//  }
//  free(lines);
int file_to_arr(char *file_name, size_t max_file_size, char **lines,
                size_t max_rows, size_t max_cols, int lines_rows) {

  lines = malloc(sizeof(char *) * max_rows);
  if (lines == NULL) {
    perror("malloc failed");
    return 1;
  }

  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    perror("fopen failed");
    free(lines);
    return 1;
  }

  char line[max_cols];
  int line_num = 0;

  while (fgets(line, max_cols, file) != NULL && line_num < max_rows) {
    lines[line_num] = malloc(sizeof(char) * (strlen(line) + 1));
    if (lines[line_num] == NULL) {
      perror("malloc failed for lines[line_num]");
      for (int i = 0; i < line_num; i++) {
        free(lines[i]);
      }
      free(lines);
      fclose(file);
      return 1;
    }
    strcpy(lines[line_num], line);
    size_t len = strlen(lines[line_num]);
    if (len > 0 && lines[line_num][len - 1] == '\n') {
      lines[line_num][len - 1] = '\0';
    }
    line_num++;
  }
  fclose(file);

  lines_rows = line_num;
  return 0;
}

