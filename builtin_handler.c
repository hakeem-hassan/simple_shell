#include <stdlib.h>
#include "hsh.h"

/**
 * handle_setenviron -The set environment variable with given name and value.
 * @arg: String containing name and value separated by a space.
 */
void handle_setenv(char *arg)
{
	char *name = _strtok(arg, " ");
	char *value = _strtok(NULL, " ");

	if (name != NULL && value != NULL)
	{
		handle_special_characters(value);

		if (setenv(name, value, 1) != 0)
			fprintf(stderr, "setenv: Unable to set environment variable\n");
	}
	else
		fprintf(stderr, "setenv: Invalid syntax\n");
}

/**
 * handle_unsetenvirn -The Unset environment variable with given name.
 * @arg: String containing the name of the variable to unset.
 */
void handle_unsetenv(char *arg)
{
	char *name = _strtok(arg, " ");

	if (name != NULL)
	{
		if (unsetenv(name) != 0)
			fprintf(stderr, "unsetenv: Unable to unset environment variable\n");
	}
	else
		fprintf(stderr, "unsetenv: Invalid syntax\n");
}

/**
 * handle_exit - Exit the shell with the specified exit code.
 * @arg: String containing the exit code as a decimal number.
 */
void handle_exit(char *arg)
{
	char *endptr;
	long exitCode = strtol(arg, &endptr, 10);

	if (*endptr == '\0')
		exit(exitCode);
	else
		fprintf(stderr, "/bin/sh: 3: exit: Illegal number: %s\n", arg);
}

/**
 * handle_environ - Display the current environment variables.
 */
void handle_env(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
		printf("%s\n", *env);
}

/**
 * handle_cd - Change the current working directory.
 * @dir: Target directory to change to, or NULL for the home directory.
 */
void handle_cd(char *dir)
{
	char *home_dir = getenv("HOME"), current_dir[MAX_ARGS];
	char *previous_dir = getenv("PWD");

	if (dir == NULL)
	{
		if (home_dir == NULL)
		{
			fprintf(stderr, "Error: HOME environment variable not set\n");
			return;
		}
		else
			chdir(home_dir);
	}
	else if (strcmp(dir, "-") == 0)
	{
		if (previous_dir == NULL)
		{
			fprintf(stderr, "Error: Previous directory not set\n");
			return;
		}
		else
			chdir(previous_dir);
	}
	else if (chdir(dir) != 0)
	{
		perror("chdir");
		return;
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return;
	}
	if (setenv("PWD", current_dir, 1) != 0)
	{
		perror("setenv");
		return;
	}
}
