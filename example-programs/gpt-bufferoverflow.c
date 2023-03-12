#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int main() {
  int* ptr = NULL;
  int i, n;

  n = 10;

  ptr = (int*)malloc(n * sizeof(int));
  if (ptr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  for (i = 0; i < n; i++) {
    ptr[i] = i + 1;
  }

  printf("The integers are: ");
  for (i = 0; i <= n; i++) {
    printf("%d ", ptr[i]);
  }
  printf("\n");

  free(ptr);
  
  return 0;
}