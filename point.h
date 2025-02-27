#ifndef POINT_H
#define POINT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point *data;
  int length;
  int capacity;
} PointArray;

Point createPoint(int x, int y) { return (Point){x, y}; }

PointArray createPointArray(int capacity) {
  Point *data = calloc(capacity, sizeof(Point));
  int length = 0;
  return (PointArray){data, length, capacity};
}

void addPoint(PointArray *arr, int x, int y) {
  if (arr->length < arr->capacity) {
    arr->data[arr->length++] = (Point){x, y};
  } else {
    printf("PointArray is full.\n");
  }
}

void printPointArray(PointArray arr) {
  printf("PointArray (%d Points): ", arr.length);
  for (int i = 0; i < arr.length; i++) {
    printf("%d:(%d,%d)", i, arr.data[i].x, arr.data[i].y);
    if (i < arr.length - 1) {
      printf(",");
    }
    if (i == arr.length - 1) {
      printf("\n");
    }
  }
}

Point createPoint(int x, int y);
PointArray createPointArray(int capacity);
void addPoint(PointArray *arr, int x, int y);
void printPointArray(PointArray arr);

#endif // POINT_H
