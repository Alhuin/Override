#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *a_user_name;

int verify_user_name(void)
{
    puts("verifying username....\n");
    return strcmp(a_user_name, "dat_wil");
}

int verify_user_pass(char *password)
{
    return strcmp(password, "admin");
}

int main()
{
    char    *buffer;
    int     check_pass;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);
    
    if (verify_user_name() != 0)
    {
        puts("nope, incorrect username...\n");
        return(1);
    }

    puts("Enter Password: ");
    fgets(buffer, 100, stdin);

    check_pass = verify_user_pass(buffer);
    if (check_pass == 0)
    {
        puts("nope, incorrect password...\n");
        return(1);
    }
    if (check_pass == 0)
        return(0);
    return (0);
}
