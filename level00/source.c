#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int input;
  
	puts("***********************************");
	puts("* \t	 -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &input);
	if (input == 5276)
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
		return (0);
	}
	puts("\nInvalid Password!");
	return (1);
}
