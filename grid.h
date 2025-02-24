#ifndef GRID_H
#define GRID_H

#include <stdlib.h>

typedef struct {
  void *data;
  int rows;
  int cols;
} Grid;

Grid createGrid(int rows, int cols, char d) {
  Grid grid;
  grid.data = malloc(sizeof(char*) * rows * cols);
  return grid;
}

#endif // GRID_H
