#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void substr_m(char *src, char *dest, int start, int length) {
  assert(src != NULL);
  assert(dest != NULL);
  assert(start >= 0);
  assert(length >= 0);
  assert(start + length <= strlen(src));


  strncpy(dest, src + start, length);
  dest[length] = '\0';
}


void strncpy_m(char *src, char *dest, int start, int length) {
  int i = 0;
  src += start;
  while (length--)
    *dest++ = *src++;
  *dest = '\0';
} 

// for learning purposes
size_t len_m(char *str) {
  char *s;
  for (s = str; *s; ++s)
    ;
  return s - str;
}

// Converts a string into an array of integers.
// Args: string, integer
// Modifies: elements
// Returns: integer array
int* get_array_from_csv_int(char* str, int* elements) {
  char *copy=strdup(str);
  char *token=strtok(copy, ",");
  int count = 0;
  while(token != NULL) {
    count++;
    token = strtok(NULL, ",");
  }
  *elements = count;

  int *arr = malloc(sizeof(int) * count);
  if (arr==NULL){
    free(copy);
    return NULL;
  }

  // need to reset the string b/c \0 replaced delims
  strcpy(copy,str);
  token=strtok(copy, ",");
  int i = 0;
  while(token != NULL) {
    arr[i] = atoi(token);
    /*printf("token: %s\n", token);*/
    /*printf("arr[%d]: %d\n", i, arr[i]);*/
    /*sscanf(token, "%d,", arr[i++]);*/
    i++;
    token = strtok(NULL, ",");
  }

  free(copy);
  return arr;
}
