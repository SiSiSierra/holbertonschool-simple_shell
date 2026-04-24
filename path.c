#include "shell.h"

/**
 * get_path - separates the path directories from env
 * @env: pointer to array of environment variables
 *
 * Return: String of just the PATH section of env
 */

char *get_path(char **env)
{
	int i = 0;
	char *temp = NULL;
	char *env_var = NULL;
	char *path_dirs = NULL;
	char *path_dirs_cp = NULL;

	while (env[i])
	{
		temp = strdup(env[i]);
		env_var = strtok(temp, "=");
		if ((strcmp(env_var, "PATH")) == 0)
		{
			path_dirs = strtok(NULL, "=");
			break;
		}
		free(temp);
		i++;
	}
	if (path_dirs == NULL)
	{
		return (NULL);
	}
	path_dirs_cp = strdup(path_dirs);
	free(temp);
	return (path_dirs_cp);
}

/**
 * get_path_directories - split the PATH string into an array of strings with
 * each directory as their own entry
 * @path: path string to split
 *
 * Return: Array of directories from PATH
 */
char **get_path_directories(char *path)
{
	char **path_dirs;
	char *dir;
	char *temp = strdup(path);
	int i = 0;

	dir = strtok(temp, ":");
	while (dir != NULL)
	{
		i++;
		dir = strtok(NULL, ":");
	}
	free(temp);
	path_dirs = malloc((i + 1) * sizeof(*path_dirs));
	if (!path_dirs)
	{
		return (NULL);
	}
	i = 0;
	for (dir = strtok(path, ":"); dir; dir = strtok(NULL, ":"))
	{
	path_dirs[i] = dir;
		i++;
	}
	path_dirs[i] = NULL;
	return (path_dirs);
}

/**
 * strcat3 - concatenates 3 strings together.
 * @a: first string
 * @b: middle string
 * @c: last string
 *
 * Return: final string with all 3 concatenated.
 */
char *strcat3(char *a, char *b, char *c)
{
	size_t size = strlen(a) + strlen(b) + strlen(c) + 1;
	char *str = malloc(size);

	strcpy(str, a);
	strcat(str, b);
	strcat(str, c);

	return (str);
}

/**
 * check_arg - Returns the full name of given argument
 * @args: array of arguments to run
 * @path_directories: array of all PATH directories
 * @flag: flag to change based on args[0]
 *
 * Return: full argument name if found, NULL otherwise.
 */
char *check_arg(char **args, char **path_directories, int *flag)
{
	char *temp = NULL;
	int i = 0;
	struct stat test;

	if (args == NULL)
	{
		return (NULL);
	}
	if (*args[0] == '/' || *args[0] == '.')
	{
		if (stat(args[0], &test) == 0)
		{
			*flag = 0;
			return (args[0]);
		}
		else
		{
			*flag = -1;
			return (NULL);
		}
	}
	else
	{
		while (path_directories != NULL && path_directories[i])
		{
			temp = strcat3(path_directories[i], "/", args[0]);
			if (stat(temp, &test) == 0)
			{
				*flag = 1;
				return (temp);
			}
			else
			{
				i++;
				free(temp);
			}
		}
		temp = NULL;
	}
	*flag = -1;
	return (temp);
}
