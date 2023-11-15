#include "shell.h"

int main(void)
{
	char *buffer;
	size_t bufsize = 1024;
	ssize_t characters;
	pid_t child_pid;
	int status;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while (1)
	{
		printf("#cisfun$ ");
		characters = getline(&buffer, &bufsize, stdin);

		if (characters == EOF)
		{
			printf("\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		if (buffer[characters - 1] == '\n')
		{
			buffer[characters - 1] = '\0';
		}

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error creating child process");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{

			char *args[2];
			args[0] = buffer;
			args[1] = NULL;

			if (execve(buffer, args, NULL) == -1)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return 0;
}
