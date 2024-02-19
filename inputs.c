#include "S_shell.h"

/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: Inputs file          */
/*                                                     */
/*              Created by: CASSIAN KIRAGU             */
/*                          KINGSON BUNDI MWAI         */
/* *************************************************** */

void *_realloc(void *ptr, size_t older_size, size_t newer_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates memory.
 * @ptr: A pointer pointing to the previous mem
 * @older_size: allocated mem size to the pointer
 * @newer_size: size of the mem to the pointer.
 * Return: pointer to the reallocated memory new_ptr
 */
void *_realloc(void *ptr, size_t older_size, size_t newer_size)
{
	void *memory;
	char *new_ptr, *content;
	unsigned int idx;

	if (newer_size == older_size)
		return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(newer_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (newer_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = ptr;
	memory = malloc(sizeof(*new_ptr) * newer_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	content = memory;

	for (idx = 0; idx < older_size && idx < newer_size; idx++)
		content[idx] = *new_ptr++;

	free(ptr);
	return (memory);
}

/**
 * assign_lineptr - changes the lineptr variable to _getline.
 * @lineptr: A storage buffer for input.
 * @n: lineptr length
 * @buffer: lineptr memory block
 * @b: buffer size.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - User input
 * @lineptr: storage buffer for input.
 * @n: lineptr size
 * @stream: The input string.
 * Return: input read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t output;
	char content = 'x', *buffer_store;
	int reader;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer_store = malloc(sizeof(char) * 120);
	if (!buffer_store)
		return (-1);

	while (content != '\n')
	{
		reader = read(STDIN_FILENO, &content, 1);
		if (reader == -1 || (reader == 0 && input == 0))
		{
			free(buffer_store);
			return (-1);
		}
		if (reader == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer_store = _realloc(buffer_store, input, input + 1);

		buffer_store[input] = content;
		input++;
	}
	buffer_store[input] = '\0';

	assign_lineptr(lineptr, n, buffer_store, input);

	output = input;
	if (reader != 0)
		input = 0;
	return (output);
}
