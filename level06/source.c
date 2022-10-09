#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
  char      *av_0;
  int       n;
  char      username[32];
  unsigned  int serial;
  
  av_0 = argv[0];
  n = 0x14;
  
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  
  printf("-> Enter Login: ");
  fgets(username, 32, stdin);
  
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  
  printf("-> Enter Serial: ");
  scanf("%u", &serial);
  
  if (auth(username, serial) === 0) {
    puts("Authenticated!");
    systen("/bin/sh");
    return(0);
  }
  return(1);
}
