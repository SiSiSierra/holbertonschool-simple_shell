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
	int idx = 0;

	token = strtok(str, " ");
	while (token != NULL)
	{
		idx++;
		token = strtok(NULL, " ");
	}
	free(str);

	args = malloc((idx + 1) * sizeof(*args));
	if (!args)
	{
		return (NULL);
	}
	idx = 0;
	for (token = strtok(line, " "); token; token = strtok(NULL, " "))
	{
		args[idx] = token;
		idx++;
	}
	args[idx] = NULL;
	return (args);
}

/**
 * shell_exec - forks a child and runs execve with args
 * @args: arguments to run with execve
 * @argv: arguments from command line
 * @env: environment variables
 */
void shell_exec(char **args, char **argv, char **env)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		execve(args[0], args, env);
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
	char *line;
	size_t bufsize;
	char **args;
	int args_len, loop = 0;

	(void)argc;
	while (loop != 1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}
		getline(&line, &bufsize, stdin);
		if (feof(stdin))
		{
			printf("EOF\n");
			loop = 1;
		}
		line[strcspn(line, "\n")] = '\0';
		if (loop != 1)
		{
			args = get_tokens(line);
			args_len = 0;
			while (args[args_len])
			{
			args_len++;
			}
		}
		else
		{
			args[0] = NULL;
		}
		shell_exec(args, argv, env);
		free(line);
		line = NULL;
		if (loop != 1)
			free(args);
	}
	return (EXIT_SUCCESS);
}
