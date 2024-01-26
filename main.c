#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Cleans up allocated memory and exits the program.
 *
 * This function prints a newline, frees the memory allocated for the buffer,
 * and exits the program with a success status.
 *
 * @param buffer The allocated buffer to be freed.
 */
void cleanup(char *buffer)
{
	printf("\n");
	free(buffer);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Executes a command using execve.
 *
 * This function constructs an argument array and uses execve to execute a command.
 * If the command is not found, it prints an error message and exits with a failure status.
 *
 * @param buffer The command to be executed.
 */
void execute_command(char *buffer)
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

/**
 * @brief The main function of the simple shell.
 *
 * This function implements a basic shell that prompts the user for commands,
 * executes them using fork and execve, and waits for the child process to complete.
 *
 * @return 0 on successful execution.
 */
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
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		printf("#cisfun$ ");
		characters = getline(&buffer, &bufsize, stdin);

		if (characters == EOF)
		{
			cleanup(buffer);
		}

		// Remove the newline character
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
			// Child process
			execute_command(buffer);
		}
		else
		{
			// Parent process
			wait(&status);
		}
	}

	return 0;
}
