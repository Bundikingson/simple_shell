/* *************************************************** */
/*                                                     */
/*                                                     */
/*     Function of file:  partition_handlers.c         */
/*                                                     */
/*              Created by: CelsusK                 */
/*                          Bundi Kingson                  */
/* *************************************************** */

#include "S_shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - handles line partitions ";", "||", and "&&" by ADDING SPACE
 * and uses '\0' instead of #.
 * @line: line pointer pointing to the standard input being READ..
 * @READ: number of words being READ..
 */

void handle_line(char **line, ssize_t read)

{
	char *prev_line, *nxt_line;
	char previous, current, next;
	size_t content, input;
	ssize_t new_length;

	new_length = get_new_len(*line);
	if (new_length == read - 1)
		return;
	nxt_line = malloc(new_length + 1);
	if (!nxt_line)
		return;
	input = 0;
	prev_line = *line;
	for (content = 0; prev_line[content]; content++)
	{
		current = prev_line[content];
		next = prev_line[content + 1];
		if (content != 0)
		{
			previous = prev_line[content - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					nxt_line[input++] = ' ';
					nxt_line[input++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					nxt_line[input++] = ';';
					nxt_line[input++] = ' ';
					continue;
				}
				if (previous != ' ')
					nxt_line[input++] = ' ';
				nxt_line[input++] = ';';
				if (next != ' ')
					nxt_line[input++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					nxt_line[input++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					nxt_line[input++] = '&';
					nxt_line[input++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					nxt_line[input++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					nxt_line[input++] = '|';
					nxt_line[input++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (content != 0 && prev_line[content - 1] != ' ')
				nxt_line[input++] = ' ';
			nxt_line[input++] = ';';
			if (next != ' ' && next != ';')
				nxt_line[input++] = ' ';
			continue;
		}
		nxt_line[input++] = prev_line[content];
	}
	nxt_line[input] = '\0';

	free(*line);
	*line = nxt_line;
}

/**
 * get_new_len - DISPLAYS size of line partitioned by ";", "||", "&&&", or "#"..
 * @line: LINE checked..
 * RETURN: LINE size..
 */

ssize_t get_new_len(char *line)

{
	size_t content;
	ssize_t new_length = 0;
	char current, next;

	for (content = 0; line[content]; content++)
	{
		current = line[content];
		next = line[content + 1];
		if (current == '#')
		{
			if (content == 0 || line[content - 1] == ' ')
			{
				line[content] = '\0';
				break;
			}
		}
		else if (content != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[content - 1] != ' ' && line[content - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[content - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[content - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				logical_ops(&line[content], &new_length);
		}
		else if (current == ';')
		{
			if (content != 0 && line[content - 1] != ' ')
				new_length++;
			if (next != ' ' && next != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
/**
 * logical_ops - SEARCHES for "||" or "&&" in INPUT..
 * @line: A POINTER to check in the INPUT..
 * @new_len: POINTER pointing to new_len in get_new_len FUNCTION..
 */

void logical_ops(char *line, ssize_t *new_len)

{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
