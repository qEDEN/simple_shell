#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Execute a shell command.
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char **args = malloc(2 * sizeof(char *));

		if (args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		args[0] = command;
		args[1] = NULL;

		execvp(args[0], args);

		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			printf("Command executed successfully\n");
		}
	}
}

/**
 * main - Main function of the simple shell.
 * Return: 0 on success.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		printf("Enter a command: ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break;
		}

		/* Remove trailing newline character */
		input[strcspn(input, "\n")] = '\0';

		execute_command(input);
	}

	return (0);
}
