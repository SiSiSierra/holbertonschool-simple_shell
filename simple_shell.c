#include "shell.h"

/**
 * get_tokens - separate the string from line into tokens
 * @line: string input to get tokens from
 *
 * Return: array of char of arguments
 */
char **get_tokens(char *line)
{
	char **args = NULL;
	char *token = NULL;
	char *str = strdup(line);
	int i = 0;

	token = strtok(str, " \n");
	while (token != NULL)
	{
		i++;
		token = strtok(NULL, " \n");
	}
	free(str);

	args = malloc((i + 1) * sizeof(*args));
	if (!args)
	{
		return (NULL);
	}
	i = 0;
	token = strtok(line, " \n");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;
	return (args);
}

/**
 * shell_exec - forks a child and runs execve with args
 * @args: arguments to run with execve
 * @argv: arguments from command line
 * @env: environment variables
 * @path_directories: Array of strings with all directories from PATH
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
			_exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
	else
		printf("%s: No such file or directory\n", argv[0]);
	if (flag == 1)
	{
		free(full_name);
	}
}

/**
 * prompt - prints out the prompt for shell
 * @msg: message to print out for the prompt
 */
void prompt(char *msg)
{
	if (isatty(STDIN_FILENO))
	{
		printf("%s", msg);
		fflush(stdout);
	}
}

/**
 * shell_interactive - Use the shell as a command line
 * @argv: Array of arguments from command line
 * @env: Array of environment variables
 * @path_directories: Array of strings with all directories from PATH
 * Return: 1 if finished, 0 if to continue
 */
int shell_interactive(char **argv, char **env, char **path_directories)
{
	char *line = NULL;
	size_t bufsize = 0;
	char **args = NULL;
	int args_len = 0, read, i, loop = 0;

	prompt("#cisfun$ ");
	read = getline(&line, &bufsize, stdin);
	if (read > 1 && line[read - 1] == '\n')
		line[read - 1] = '\0';
	if (read == -1 || check_all_whitespace(line) == 1)
	{
		free(line);
		return (1);
	}
	args = get_tokens(line);
	args_len = get_arr_len(args);
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		return (1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		free(args);
		free(line);
		print_env(env);
		return(loop);
	}
	shell_exec(args, argv, env, path_directories);
	i = 0;
	while (i < args_len)
	{
		free(args[args_len]);
		i++;
	}
	free(args);
	free(line);
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
