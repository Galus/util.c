#ifndef DBG_H
#define DBG_H

#include <stddef.h>
#include <stdio.h>

void print_hex_memory(const void *ptr, size_t n);

void print_hex_memory(const void *ptr, size_t n) {
  if (ptr == NULL) {
    fprintf(stderr, "Error: Pointer is NULL\n");
    return;
  }

  if (n == 0) {
    printf("No bytes to print.\n");
    return;
  }

  const unsigned char *bytes =
      (const unsigned char *)ptr; // Treat as unsigned char array
  uintptr_t address =
      (uintptr_t)ptr; // Store the address as an unsigned integer

  printf("Memory dump of %zu bytes starting at address %p:\n", n, ptr);

  for (size_t i = 0; i < n; i++) {
    if (i % 16 == 0) { // New line every 16 bytes
      if (i > 0) {
        printf("  "); // Spacer after hex values
        for (size_t j = i - 16; j < i; j++) {
          if (bytes[j] >= 32 && bytes[j] <= 126) { // Printable ASCII
            printf("%c", bytes[j]);
          } else {
            printf("."); // Non-printable character
          }
        }
      }
      printf(
          "\n%p: ",
          (void *)(address + i)); // Print address at the beginning of the line
    }
    printf("%02X ", bytes[i]); // Print hex value with leading zero if needed
  }
  // Handle any remaining bytes on the last line
  if (n % 16 != 0) {
    int padding = 16 - (n % 16);
    for (int i = 0; i < padding; i++) {
      printf("   "); // Add padding for alignment
    }
    printf("  ");
    for (size_t j = n - (n % 16); j < n; j++) {
      if (bytes[j] >= 32 && bytes[j] <= 126) {
        printf("%c", bytes[j]);
      } else {
        printf(".");
      }
    }
  }
  printf("\n");
}

#endif // DBG_H
