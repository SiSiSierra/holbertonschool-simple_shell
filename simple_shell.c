#include "shell.h"

/**
 * get_tokens - separate the string from line into tokens
 * @line: string input to get tokens from
 *
 * Return: array of char of arguments
 */
char **get_tokens(char *line)
{
	char **args;
	char *token;
	char *str = strdup(line);
	int i = 0;

	token = strtok(str, " ");
	while (token != NULL)
	{
		i++;
		token = strtok(NULL, " ");
	}
	free(str);

	args = malloc((i + 1) * sizeof(*args));
	if (!args)
	{
		return (NULL);
	}
	i = 0;
	for (token = strtok(line, " "); token; token = strtok(NULL, " "))
	{
		args[i] = token;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/**
 * shell_exec - forks a child and runs execve with args
 * @args: arguments to run with execve
 * @argv: arguments from command line
 * @env: environment variables
 */
void shell_exec(char **args, char **argv, char **env, char **path_directories)
{
	int flag = 0;
	char *full_name = check_arg(args, path_directories, &flag);
	pid_t child_pid;

	if (flag != -1)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if (args == NULL)
				_exit(0);
			execve(full_name, args, env);
			if (args[0] == NULL)
			{
				printf("%s\n", args[0]);
			}
			printf("%s: No such file or directory\n", argv[0]);
			_exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
	if (flag == 1)
		free(full_name);
}

/**
 * shell_interactive - Use the shell as a command line
 * @argv: Array of arguments from command line
 * @env: Array of environment variables
 * Return: 1 if finished, 0 if to continue
 */
int shell_interactive(char **argv, char **env, char **path_directories)
{
	char *line;
	size_t bufsize;
	char **args;
	int loop = 0;

	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
	getline(&line, &bufsize, stdin);
	if (feof(stdin))
	{
		free(line);
		return (1);
	}
	line[strcspn(line, "\n")] = '\0';
	args = get_tokens(line);
	if (strcmp(args[0], "exit") == 0)
	{
		printf("Shell ending\n");
		free(args);
		free(line);
		return (1);
	}
	shell_exec(args, argv, env, path_directories);
	return (loop);
}


/**
 * main - entry point
 * @argc: number of arguments from command line
 * @argv: array of arguments from command line
 * @env: array of environment variables
 *
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	char *path = get_path(env);
	char **path_directories = get_path_directories(path);

	if (argc > 1)
	{
		shell_exec(&(argv[1]), argv, env, path_directories);
	}
	else
	{
		while (shell_interactive(argv, env, path_directories) != 1)
		{}
	}
	free(path);
	free(path_directories);
	return (EXIT_SUCCESS);
}
