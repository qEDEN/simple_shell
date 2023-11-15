#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * main - Simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	while (1)
	{
		char command[MAX_COMMAND_LENGTH];
		pid_t pid;

		display_prompt();
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\nExiting shell.\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			break;
		}

		pid = fork();

		if (pid == 0)
		{
			if (execlp(command, command, (char *)NULL) == -1)
			{
				perror(command);
			}
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			int status;
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork");
		}
	}

	return 0;
}
