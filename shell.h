#ifndef SHELL_H
#define SHELL_H

/*
 * Headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
 *  Prototype Functions
 */
char **get_tokens(char *line);
void shell_exec(char **args, char **argv, char **env);
char *get_path(char **env);
char **get_path_directories(char *path);

#endif
