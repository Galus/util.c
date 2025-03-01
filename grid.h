#ifndef GRID_H
#define GRID_H

#include "point.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000

typedef struct {
  char **data;
  int rows;
  int cols;
} Grid;

/*bool insideGrid(const Grid * grid, int x, int y) {*/
/*  if (x <= 0 || y <= 0 || x >) {*/
/**/
/*  }*/
/*}*/

enum Direction { RIGHT, DOWN, LEFT, UP, DIRECTION_COUNT };

const char *directionName(enum Direction dir) {
  static const char* directionStrings[] = {
    "RIGHT", "DOWN", "LEFT", "UP"
  };
  if (dir >= 0 && dir < DIRECTION_COUNT) {
    return directionStrings[dir];
  } else {
    return "UNKNOWN";
  }
}

void printDirection(enum Direction dir) {
  switch (dir) {
  case RIGHT:
    printf("RIGHT");
    break;
  case DOWN:
    printf("DOWN");
    break;
  case LEFT:
    printf("LEFT");
    break;
  case UP:
    printf("UP");
    break;
  default:
    printf("Unknown Direction"); // Handle unexpected values
    break;
  }
}

void printGridDimensions(Grid *g) { printf("%dx%d\n", g->rows, g->cols); }

Grid *createGrid(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    fprintf(stderr, "Invalid grid dimensions.\n");
    return NULL;
  }

  Grid *grid = (Grid *)malloc(sizeof(Grid));
  if (grid == NULL) {
    perror("Memory allocation failed for Grid");
    return NULL;
  }

  grid->rows = rows;
  grid->cols = cols;
  grid->data = (char **)malloc(rows * sizeof(char *));
  if (grid->data == NULL) {
    perror("Memory allocation failed for grid rows");
    free(grid);
    return NULL;
  }

  for (int y = 0; y < rows; y++) {
    grid->data[y] = (char *)malloc(cols * sizeof(char));
    if (grid->data[y] == NULL) {
      perror("Memory allocation failed for grid cols");
      for (int i = 0; i < y; i++) {
        free(grid->data[i]);
      }
      free(grid->data);
      free(grid);
      return NULL;
    }
  }
  return grid;
}

bool isInBounds(const Grid *grid, int row, int col) {
  return !(grid == NULL || row < 0 || col < 0 || row >= grid->rows ||
           col >= grid->cols);
}

Grid *copyGrid(const Grid *original) {
  if (original == NULL) {
    return NULL;
  }

  Grid *copy = createGrid(original->rows, original->cols);
  if (copy == NULL) {
    return NULL;
  }

  for (int y = 0; y < original->rows; y++) {
    for (int x = 0; x < original->cols; x++) {
      copy->data[y][x] = original->data[y][x];
    }
  }

  return copy;
}

char *getGridCharValue(const Grid *grid, int row, int col, bool *error) {
  if (grid == NULL || row < 0 || col < 0 || row >= grid->rows ||
      col >= grid->cols) {
    if (error != NULL) {
      *error = true;
      return NULL;
    }
  }
  if (error != NULL) {
    *error = false;
  }
  return &grid->data[row][col];
}

int getGridIntValue(const Grid *grid, int row, int col, bool *error) {
  if (grid == NULL || row < 0 || col < 0 || row >= grid->rows ||
      col >= grid->cols) {
    if (error != NULL) {
      *error = true;
      return 0;
    }
  }
  if (error != NULL) {
    *error = false;
  }
  return grid->data[row][col] - '0';
}

bool setGridCharValue(Grid *grid, int row, int col, char value) {
  if (grid == NULL || row < 0 || row >= grid->rows || col < 0 ||
      col >= grid->cols) {
    return false;
  }
  grid->data[row][col] = value;
  return true;
}

void freeGrid(Grid *grid) {
  if (grid != NULL) {
    for (int i = 0; i < grid->rows; i++) {
      free(grid->data[i]);
    }
    free(grid->data);
    free(grid);
  }
}

void printCharGridAsciiCodes(const Grid *grid) {
  if (grid == NULL) {
    printf("Grid is NULL.\n");
    return;
  }

  for (int row = 0; row < grid->rows; row++) {
    for (int col = 0; col < grid->cols; col++) {
      printf("%d ", *getGridCharValue(grid, row, col, NULL));
    }
    printf("\n");
  }
}

void printCharGrid(const Grid *grid) {
  if (grid == NULL) {
    printf("Grid is NULL.\n");
    return;
  }

  for (int row = 0; row < grid->rows; row++) {
    for (int col = 0; col < grid->cols; col++) {
      printf("%c ", *getGridCharValue(grid, row, col, NULL));
    }
    printf("\n");
  }
}

Grid *createGridFromFile(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file");
  }

  int rows = 0, cols = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, fp)) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
      len--;
    }
    rows++;
    if ((int)len > (unsigned long)cols) {
      cols = (int)len;
    }
  }

  Grid *grid = createGrid(rows, cols);
  if (grid == NULL) {
    fprintf(stderr, "Failed to create grid.\n");
    fclose(fp);
    return NULL;
  }

  rewind(fp);
  int y = 0;
  while (fgets(line, MAX_LINE_LENGTH, fp)) {
    /*printf("line %d: %s\n", y, line);*/
    for (int x = 0; x < cols; x++) {
      if (x < (int)strlen(line)) {
        grid->data[y][x] = line[x];
      } else {
        grid->data[y][x] = ' ';
      }
    }
    y++;
  }

  fclose(fp);
  return grid;
}

#endif // GRID_H
