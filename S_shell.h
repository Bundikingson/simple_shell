#ifndef _shell_
#define _shell_

/* *********************************************/
/*                                             */
/*       File function   : Header file         */
/*                                             */
/*                 Made by: CASSIAN KIRAGU     */
/*                          KINGSON BUNDI MWAI */
/* ******************************************* */

/*Include the libraries to be used*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/stat.h>

/*Declare how to exit and end  of the file will be executed*/
#define END_OF_FILE -2
#define EXIT -3

/*Declare  global variable name for the program*/

char *name;
/* Declare global variables to be used in the global environment*/
extern char **environ;
/* Declare global variable for history*/
int history;


/* Defining the structure of a linked list*/

/**
 * struct list_struct - Structure for defining a linked list
 * @directory: a pointer to the directory's path
 * @next: A pointer to another structure
 */

typedef struct list_struct
{
	char *directory;
	struct list_struct *next;
} list_t;


/* Defining a structure for builtin apis*/

/**
 * struct builtin_struct - Builtin commands’ structure
 * @name: Builtin command  name
 * @fn:  Builtin command's function pointer.
 */
typedef struct builtin_struct
{
	char *name;
	int (*zn)(char **argv, char **front);
} builtin_t;

/* Defining a structure for aliases*/

/**
 * struct alias_struct - structure to declare aliases.
 * @name: Alias name.
 * @value: Alias content.
 * @next: Pointer to another struct alias_s.
 */
typedef struct alias_struct
{
	char *name;
	char *value;
	struct alias_struct *next;
} alias_t;


/* Declaring a global alias linked list */
alias_t *aliases;


/* Main helpers */
ssize_t _getline(char **lineptr, size_t *k, FILE *stream);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

/* Input helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* String Functions */
int _strlen(const char *u);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t k);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *u, char d);
int _strspn(char *u, char *accept);
int _strcmp(char *u1, char *u2);
int _strncmp(const char *u1, const char *u2, size_t k);

/* Built-ins */
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Built-in helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/* malloc_checked - checks for malloc */
void *malloc_checked(unsigned int b);
int proc_file_commands(char *file_path, int *exe_ret);
#endif
