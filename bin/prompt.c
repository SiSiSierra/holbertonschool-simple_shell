#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	size_t bufsize = 0;
	char *buf = NULL;

	printf("$ ");
	getline(&buf, &bufsize, stdin);
	printf("%s", buf);
	free(buf);
	return (0);
}
