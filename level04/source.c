#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int	main(void)
{
	int		pid = fork();
	char	*buffer;
	int		ret = 0;
	int		status = 0;

	memset(buffer, 0, 32);

	if (pid == 0) {
		prctl(1, 1);
		ptrace(0, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
    return(0);
	}

  while (ret = ptrace(3, pid, 44, 0) != 11) {
    wait(&status);
    if (status & 0x7f == 0 || (status & 0x7f) >> 1 <= 0) {
      puts("child is exiting...");
      return (0);
    }
  }    

	puts("no exec() for you");
	kill(pid, 9);
	return(0);
}
