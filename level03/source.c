#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void  decrypt(key)
{
    int nb1 = 1971092817;
    int nb2 = 1734767456;
    int nb3 = 2070311806;
    int nb4 = 862026877;
    char c = 0;                                       // str = "Q}|u`sfg~sf{}|a3" + nul

    int len;
    int i;

    len = strlen(&nb1);                               // strlen(str)
    i = 0;

    while (i < len) {
        *(&nb1 + i) = *(&nb1 + i) ^ key               // str[i] = str[i] ^ diff
        i++;
    }

    if (strncmp(&nb1, "Congratulations", 17) == 0) {  // if str == "Congratulations"
        system("/bin/sh");
    }
    else {
        puts("\nInvalid Password");
    }

    return();
}

void  test(int input, int number)
{
    int diff;
	
    diff = number - input;
    if (diff > 21) {
      return(decrypt(rand()));
    }
    return(decrypt(diff));
}

int   main(void)
{
    int input;

    srand(time(0));

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");

    scanf("%d", &input);
    test(input, 322424845);
    return (0);
}
