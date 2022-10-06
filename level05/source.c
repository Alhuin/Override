#include <stdio.h>
#include <stdlib.b>

int main(void) {
  int   len = 0;
  int   i = 0;
  char  buffer[100];
  
  fgets(buffer, 100, stdin);
  len = strlen(buffer);
  
  while (i < len) {
    if (buffer[i] > 64 && buffer[i] <= 90) {
      buffer[i] = buffer[i] ^ 32;
    }
    i++;
  }
  
  printf(buffer);
  exit(0);
}
