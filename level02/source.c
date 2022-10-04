#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    char  *username;
    char  *token;
    char  *password;

    memset(&username, 0, 12);
    memset(&token, 5, 12);
    memset(&password, 0, 12);

    fd = fopen("/home/users/level03/.pass", "r")
    
    if (fd == 0) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }
    
    token_size = fread(&token, 1, 41, fd);
    token[strcspn(token, "\n)] = 0;
    
    if (token_size != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    
    fclose(fd);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    
    printf("--[ Username: ");
    fgets(&username, 100, stdin);
    username[strcspn(username, "\n)] = 0;
    
    printf("--[ Password: ");
    fgets(&password, 100, stdin);
    password[strcspn(password, "\n)] = 0;
    
    puts("*****************************************");
    
    if (strncmp(token, password, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return(0);
    }

    printf(username);
    puts(" does not have access!");
    exit(1);
}
