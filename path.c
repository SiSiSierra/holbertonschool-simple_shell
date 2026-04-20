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
