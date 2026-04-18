#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child_pid;
	pid_t parent_pid;
	int status;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};


	for (int i = 0; i < 5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			parent_pid = getppid();
			printf("My ppid is: %u\n", parent_pid);
			execve(argv[0], argv, NULL);
		}
		else
		{
			wait(&status);
			printf("Printed %d\n", i);
		}
	}
	return (0);
}
