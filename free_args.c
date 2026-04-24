#include "shell.h"

/**
 * free_args - Frees the given array
 * @args: array to free
 * @length: length of args array
 */
void free_args(char **args, int length)
{
	int i = 0;

	while (i < length)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
