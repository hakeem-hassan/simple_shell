#include "hsh.h"

/**
 * _strtok - string tokenizer function
 * @str: The string to tokenize
 * @delim: The delimiter characters
 *
 * Expanciate:
 *   This function tokenizes a string using the specified delimiter
 *   characters. It maintains state across calls and returns the next
 *   token in the string. If no more tokens are found, it returns NULL.
 *
 * Return:
 *   - A pointer to the next token in the string.
 *   - NULL if no more tokens are found or if the input string is NULL.
 */
char *_strtok(char *str, const char *delim)
{
	static char *save_ptr;
	char *token;

	if (str != NULL)
		save_ptr = str;
	else if (save_ptr == NULL)
		return (NULL);
	save_ptr += strspn(save_ptr, delim);
	if (*save_ptr == '\0')
		return (NULL);
	token = save_ptr;
	save_ptr += strcspn(save_ptr, delim);
	if (*save_ptr != '\0')
	{
		*save_ptr = '\0';
		save_ptr++;
	}
	else
		save_ptr = NULL;

	return (token);
}

/**
 * handle_signals - signals sent to the shell.
 * @signo: The signal number.
 */
void handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n$ ");
		fflush(stdout);
	}
	else if (signo == SIGTSTP)
	{

	}
}

/**
 * _getline - To read a line from standard input
 *
 * Expanciate:
 *   This function reads a line from standard input and returns a dynamically
 *   allocated string containing the line. It uses a static buffer for
 *   efficiency and dynamically adjusts the buffer size as needed.
 *
 * Return:
 *   - A pointer to the dynamically allocated string containing the line.
 *   - NULL if the end of the input is reached or an error occurs.
 */
char *_getline()
{
	static char buffer[CHUNK_SIZE];
	static unsigned int line_size;
	ssize_t bytes_read;
	unsigned int index = 0, i, j;

	while (1)
	{
		if (index >= line_size)
		{
			line_size += CHUNK_SIZE;
			line = (char *)malloc(line_size);
			if (line == NULL)
			{
				perror("custom_getline");
				exit(EXIT_FAILURE);
			}
		}
		if (buffer[0] == '\0')
		{
			bytes_read = read(STDIN_FILENO, buffer, CHUNK_SIZE);
			if (bytes_read <= 0)
				return (NULL);
		}
		for (i = 0; buffer[0] != '\0' && buffer[0] != '\n'; ++i)
		{
			line[index++] = buffer[0];
			for (j = 0; j < CHUNK_SIZE - 1; ++j)
				buffer[j] = buffer[j + 1];
			buffer[CHUNK_SIZE - 1] = '\0';
		}
		if (buffer[0] == '\n')
		{
			buffer[0] = '\0';
			break;
		}
	}
	line[index] = '\0';

	return (line);
}
