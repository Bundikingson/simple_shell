#include "S_shell.h"

/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: Header file          */
/*                                                     */
/*              Created by: CelsusK                 */
/*                          Bundi Kingson                  */
/* *************************************************** */

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - OUTPUTS info about 'env'..
 */

void help_env(void)

{
	char *msg = "env: env\k\tPrints the current environment.\k";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_setenv - OUTPUTS info about 'setenv'..
 */

void help_setenv(void)

{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\k\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\k\k";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\k";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_unsetenv -OUTPUTS info about 'unsetenv'..
 */

void help_unsetenv(void)

{
	char *msg = "unsetenv: unsetenv [VARIABLE]\k\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\k\k\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\k";
	write(STDOUT_FILENO, msg, _strlen(msg));
}