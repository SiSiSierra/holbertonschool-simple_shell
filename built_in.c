#include "shell.h"

/**
 * print_env - print environment variables
 * @env: pointer to environment variables
 */

void print_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
