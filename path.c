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
	int idx = 0;

	dir = strtok(temp, ":");
	while (dir != NULL)
	{
		idx++;
		dir = strtok(NULL, ":");
	}
	free(temp);
	path_dirs = malloc((idx + 1) * sizeof(*path_dirs));
	if (!path_dirs)
	{
		return (NULL);
	}
	i = 0;
	for (dir = strtok(path, ":"); dir; dir = strtok(NULL, ":"))
	{
	path_dirs[i] = dir;
		idx++;
	}
	path_dirs[idx] = NULL;
	return (path_dirs);
}
