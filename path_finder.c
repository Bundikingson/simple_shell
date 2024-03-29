#include "S_shell.h"

/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: Header file          */
/*                                                     */
/*              Created by: CelsusK                 */
/*                          Bundi Kingson                 */
/* *************************************************** */

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - It searches a cmd in the PATH..
 * @command: The cmd to be found..
 * RWTURN: full pathname, else NULL, If an error occurs
 */

char *get_location(char *command)

{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->directory) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->directory);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - Copies PATH and replaces : with current working DIR..
 * @path: The colon-separated list of DIR..
 * Return: A copy of path..
 */

char *fill_path_dir(char *path)

{
	int input, count = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (input = 0; path[input]; input++)
	{
		if (path[input] == ':')
		{
			if (path[input + 1] == ':' || input == 0 || path[input + 1] == '\0')
				count += _strlen(pwd) + 1;
			else
				count++;
		}
		else
			count++;
	}
	path_copy = malloc(sizeof(char) * (count + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (input = 0; path[input]; input++)
	{
		if (path[input] == ':')
		{
			if (input == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[input + 1] == ':' || path[input + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[input], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - TOKENIZES a colon-separated dirs into linked list..
 * @path: Colon-separated dirs.
 * RETURN: A POINTER pointing to the initialized linked list..
 */

list_t *get_path_dir(char *path)

{
    int indx;
    char **dirs, *path_copy;
    list_t *head = NULL;

    path_copy = fill_path_dir(path);
    if (!path_copy)
        return NULL;
    dirs = _strtok(path_copy, ":");
    free(path_copy);
    if (!dirs)
        return NULL;

    for (indx = 0; dirs[indx]; indx++)
    {
        if (add_node_end(&head, dirs[indx]) == NULL)
        {
            free_list(head);
            free(dirs);
            return NULL;
        }
    }

    free(dirs);
    return head;
}
