#include "S_shell.h"


/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: input helpers        */
/*                                                     */
/*              Created by: CelsusK                 */
/*                          Bundi Kingson                  */
/* *************************************************** */

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
 * get_args - READS commands sent by the standard input.
 * @line: A BUFFER storage for the commands..
 * @exe_ret: Returned value of the previous executed command..
 * RETURN: NULL, if failed, else, a pointer to the stored command..
 */

char *get_args(char *line, int *exe_ret)

{
	size_t content_size = 0;
	ssize_t content;
	char *prompt = "$ ";

	if (line)
		free(line);

	content = _getline(&line, &content_size, STDIN_FILENO);
	if (content == -1)
		return (NULL);
	if (content == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[content - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, content);

	return (line);
}

/**
 * call_args - handles and calls operators FROM cmds..
 * @args: Argument input..
 * @front: POINTER pointing to the POINTER pointing..
 * to the BEGINNING of ARGS..
 * @exe_ret: RETURN value of the parent process' last executed command..
 * RETURN: The RETURN value of the last executed command..
 */

int call_args(char **args, char **front, int *exe_ret)

{
	int Return_value, indx;

	if (!args[0])
		return (*exe_ret);
	for (indx = 0; args[indx]; indx++)
	{
		if (_strncmp(args[indx], "||", 2) == 0)
		{
			free(args[indx]);
			args[indx] = NULL;
			args = replace_aliases(args);
			Return_value = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++indx];
				indx = 0;
			}
			else
			{
				for (indx++; args[indx]; indx++)
					free(args[indx]);
				return (Return_value);
			}
		}
		else if (_strncmp(args[indx], "&&", 2) == 0)
		{
			free(args[indx]);
			args[indx] = NULL;
			args = replace_aliases(args);
			Return_value = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++indx];
				indx = 0;
			}
			else
			{
				for (indx++; args[indx]; indx++)
					free(args[indx]);
				return (Return_value);
			}
		}
	}
	args = replace_aliases(args);
	Return_value = run_args(args, front, exe_ret);
	return (Return_value);
}

/**
 * run_args - IMPLEMENTS CMD execution..
 * @args: ARG input..
 * @front:  POINTER pointing to the pointer pointing
 * to the beginning ofARGS..
 * @exe_ret: The RETURN VALUE of the parent process' last executed CMD..
 * RETURN: The RETURN VALUE of the last executed CMD on the shell history..
 */

int run_args(char **args, char **front, int *exe_ret)

{
	int Return_value, input;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		Return_value = builtin(args + 1, front);
		if (Return_value != EXIT)
			*exe_ret = Return_value;
	}
	else
	{
		*exe_ret = execute(args, front);
		Return_value = *exe_ret;
	}

	history++;

	for (input = 0; args[input]; input++)
		free(args[input]);

	return (Return_value);
}

/**
 * handle_args - Executes the CMDS..
 * @exe_ret: The RETURN VAL of the parent process' last executed command..
 * Return: END_OF_FILE (-2) if an end-of-file is read, else - -1 if !tokenized..
 * O/w - Exit value of the last executed CMD..
 */

int handle_args(int *exe_ret)

{
	int Return_value = 0, indx;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (Return_value);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (indx = 0; args[indx]; indx++)
	{
		if (_strncmp(args[indx], ";", 1) == 0)
		{
			free(args[indx]);
			args[indx] = NULL;
			Return_value = call_args(args, front, exe_ret);
			args = &args[++indx];
			indx = 0;
		}
	}
	if (args)
		Return_value = call_args(args, front, exe_ret);

	free(front);
	return (Return_value);
}

/**
 * check_args - IDENTIFIES any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized CMDS and ARGS..
 * RETURN: - 2 If a ';', '&&', or '||' is at an invalid position
 * else, - 0 as ERROR STATUS
 */

int check_args(char **args)

{
	size_t input;
	char *current, *next;

	for (input = 0; args[input]; input++)
	{
		current = args[input];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (input == 0 || current[1] == ';')
				return (create_error(&args[input], 2));
			next = args[input + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[input + 1], 2));
		}
	}
	return (0);
}
