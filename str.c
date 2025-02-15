#include <assert.h>
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
