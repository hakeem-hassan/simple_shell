#include <stdlib.h>
#include "hsh.h"

/**
 * process_builtin_commands -To built-in commands or delegate
 * to external command.
 * @input: The command string to process.
 */
void process_builtin_commands(char *input)
{
	if (strcmp(input, "exit") == 0)
		fprintf(stderr, "/bin/sh: 3: exit: Illegal number: %s\n", input);
	else if (strncmp(input, "exit ", 5) == 0)
	{
		char *arg = input + 5;

		handle_exit(arg);
	}
	else if (strncmp(input, "setenv ", 7) == 0)
	{
		char *arg = input + 7;

		handle_setenv(arg);
	}
	else if (strncmp(input, "unsetenv ", 9) == 0)
	{
		char *arg = input + 9;

		handle_unsetenv(arg);
	}
	else if (strncmp(input, "cd ", 3) == 0)
	{
		char *arg = input + 3;

		handle_cd(arg);
	}
	else if (strcmp(input, "clear") == 0)
	{
		setenv("TERM", "xterm-256color", 1);
		system("clear");
	}
	else if (strcmp(input, "env") == 0)
		handle_env();
	else
		execute_command(input);
}

/**
 * Tokenize_command - Tokenize the given command into an array of arguments.
 * @command: The command string to tokenize.
 * @args: An array to store the resulting arguments.
 */
void tokenize_command(char *command, char *args[])
{
	int i = 0;
	char *token = _strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok(NULL, " ");
	}

	args[i] = NULL;
}
