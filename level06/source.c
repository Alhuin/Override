#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>
#include <stdint.h>

int auth(char *username, unsigned_int serial) {
  size_t        len;
  unsigned int  nb;
  int           i;

  username[strcspn(username, "\n")] = 0;
  len = strnlen(username, 32);
  
  if (len <= 5)
    return(1);
  if (ptrace(0, 0, 1, 0) == -1) {
    puts("\033[32m.---------------------------.");
    puts("\033[31m| !! TAMPERING DETECTED !!  |");
    puts("\033[32m'---------------------------'");
    return(1);
  }
  
  hash = hash(login);
  
  if (serial == hash) {
    return(0);
  }
  return(1);
}

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
