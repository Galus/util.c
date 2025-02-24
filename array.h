#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void *data;
  size_t length;
  size_t capacity;
  size_t elementSize;
} Array;

// signatures
void printStringArray(Array arr);
void printIntArray(Array arr);
void freeArray(Array *arr);
void freeArray(Array *arr);
void append(Array *arr, void *element);
Array createArray(size_t capacity, size_t elementSize);

Array createArray(size_t capacity, size_t elementSize) {
  Array arr;
  arr.length = 0;
  arr.capacity = capacity;
  arr.elementSize = elementSize;
  arr.data = malloc(arr.capacity * arr.elementSize);
  if (arr.data == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    arr.capacity = 0;
  }
  return arr;
}

void appendString(Array *arr, char *string) {
  if (arr->length == arr->capacity) {
    arr->capacity *= 2;
    void *newData = realloc(arr->data, arr->capacity * arr->elementSize);
    if (newData == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return;
    }
    arr->data = newData;
  }
  char *strCopy = strdup(string);
  if (strCopy == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }

  char **dest = (char **)((char *)arr->data + (arr->length * arr->elementSize));
  *dest = strCopy;

  arr->length++;
}

void append(Array *arr, void *element) {
  if (arr->length == arr->capacity) {
    arr->capacity *= 2;
    void *newData = realloc(arr->data, arr->capacity * arr->elementSize);
    if (newData == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return;
    }
    arr->data = newData;
  }
  void *dest = (char *)arr->data + (arr->length * arr->elementSize);
  memcpy(dest, element, arr->elementSize);
  arr->length++;
}

void freeArray(Array *arr) {
  free(arr->data);
  arr->data = NULL;
  arr->length = 0;
  arr->capacity = 0;
}

void freeStringArray(Array *arr) {
  char **stringData = (char **)arr->data;
  for (size_t i = 0; i < arr->length; i++) {
    free(stringData[i]);
  }
  free(arr->data);
  arr->data = NULL;
  arr->length = 0;
  arr->capacity = 0;
}

void printIntArray(Array arr) {
  int *intData = (int *)arr.data;
  for (size_t i = 0; i < arr.length; i++) {
    printf("%d", intData[i]);
    if (i < arr.length - 1) {
      printf(",");
    }
    printf("\n");
  }
}

void printStringArray(Array arr) {
  char **stringData = (char **)arr.data;
  for (size_t i = 0; i < arr.length; i++) {
    printf("%s", stringData[i]);
    if (i < arr.length - 1) {
      printf(",");
    }
    printf("\n");
  }
}

#endif
