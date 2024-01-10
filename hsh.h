#ifndef HSH_H
#define HSH_H

/**
 * Expanciate - Header file containing all function prototype used in the simple shell.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024
#define CHUNK_SIZE 64
#define MAX_ARGS 256

extern char **environ;

/* Original terminal settings */
extern struct termios orig_termios;

/* Buffer for user input */
extern char *line;

/* string-handler.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *d, char *s);
char *_strcat(char *d, char *s);
char *_strchr(char *s, char c);

/* builtin_handler.c */
void handle_setenv(char *arg);
void handle_unsetenv(char *arg);
void handle_exit(char *arg);
void handle_env(void);
void handle_cd(char *dir);

/* command_handler.c */
void tokenize_command(char *command, char *args[]);
void process_builtin_commands(char *input);

/* execute_handler.c */
void execute_command(char *command);
void execute_external_command(char *args[]);
void process_external_command(char *input);

/* external_handler.c */
char *_strtok(char *str, const char *delim);
char *_getline();
void handle_signals(int signo);

/* shell_utils.c */
void substitute_variables(char *command);
void cleanup(void);
void handle_special_characters(char *string);

/* shell.c */
void run_non_interactive_mode(void);
void run_interactive_mode(void);

#endif /* #ifndef HSH_H */
