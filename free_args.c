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

/**
 * get_arr_len - gets the length of an array
 * @arr: array to get length of
 * Return: length of given array
 */
int get_arr_len(char **arr)
{
	int len = 0;

	while (arr[len])
	{
		len++;
	}
	return (len);
}

/**
 * check_all_whitespace - Checks if given string is all whitespace
 * @line: string to check
 *
 * Return: 1 if all whitespace, 0 otherwise.
 */
int check_all_whitespace(char *line)
{
	int len = strlen(line);
	int i;

	for (i = 0; i < len; i++)
	{
		if (line[i] != ' ')
			return (0);
	}
	return (1);
}
