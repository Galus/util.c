// mem.h
#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*#define CHECK_NULL(ptr) \*/
/*  if ((ptr) == NULL) { \*/
/*    perror("ptr is null"); \*/
/*    exit(EXIT_FAILURE); \*/
/*  }*/

#define CHECK_NULL(ptr, ...)                                                   \
  if ((ptr) == NULL) {                                                         \
    if ((#__VA_ARGS__) != NULL) {                                              \
      perror(#__VA_ARGS__);                                                    \
    } else {                                                                   \
      perror("ptr is null");                                                   \
    }                                                                          \
    exit(EXIT_FAILURE);                                                        \
  }

// charptr arena, charptr current, size_t size
typedef struct {
  char *arena;
  char *current;
  size_t size;
} Arena;

inline Arena *arena_init(size_t size) {
  Arena *arena = (Arena *)malloc(sizeof(Arena));
  if (arena == NULL) {
    perror("Memory allocation failed.");
    return NULL;
  }
  arena->arena = (char *)malloc(size);
  if (arena->arena == NULL) {
    perror("Memory allocation failed.");
    return NULL;
  }

  arena->current = arena->arena;
  arena->size = size;

  return arena;
  ;
}

inline void *arena_alloc(Arena *arena, size_t size) {
  if (arena == NULL || size == 0) {
    return NULL;
  }

  if ((uintptr_t)(arena->current + size) >
      (uintptr_t)(arena->arena + arena->size)) {
    fprintf(stderr, "Arena out of memory\n");
    return NULL;
  }

  void *ptr = arena->current;
  arena->current += size;

  return ptr;
}

inline void arena_reset(Arena *arena) {
  if (arena != NULL) {
    arena->current = arena->arena;
  }
}

inline void arena_free(Arena *arena) {
  if (arena != NULL) {
    free(arena->arena);
    free(arena);
  }
}

Arena *arena_init(size_t size);
void *arena_alloc(Arena *arena, size_t size);
void arena_reset(Arena *arena);
void arena_free(Arena *arena);

#endif // MEM_H
