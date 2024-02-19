#include "S_shell.h"

/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: deltte file          */
/*                                                     */
/*              Created by: CASSIAN KIRAGU             */
/*                          KINGSON BUNDI MW           */
/* *************************************************** */
int token_len(char *str, char *deltt);
int count_tokens(char *str, char *deltt);
char **_strtok(char *line, char *deltt);

/**
 * token_len - Finds the index showing the end of
 * the first token contained within a string.
 * @str: The string to be searched.
 * @deltt: The delimiter index.
 * Return: The delimiter index showing end of initial token pointed by str.
 */
int token_len(char *str, char *deltt)
{
	int indx = 0, length = 0;

	while (*(str + indx) && *(str + indx) != *deltt)
	{
		length++;
		indx++;
	}

	return (length);
}

/**
 * count_tokens - Counts the number of the delimited words.
 * @str: The string to be searched.
 * @deltt: The delimiter character.
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *deltt)
{
	int indx, tokens = 0, length = 0;

	for (indx = 0; *(str + indx); indx++)
		length++;

	for (indx = 0; indx < length; indx++)
	{
		if (*(str + indx) != *deltt)
		{
			tokens++;
			indx += token_len(str + indx, deltt);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @deltt: The delimiter character to tokenize the string.
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *deltt)
{
	char **pointer;
	int indx = 0, tokens, content_tokens, letters, content_letters;

	tokens = count_tokens(line, deltt);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (content_tokens = 0; content_tokens < tokens; content_tokens++)
	{
		while (line[indx] == *deltt)
			indx++;

		letters = token_len(line + indx, deltt);

		pointer[content_tokens] = malloc(sizeof(char) * (letters + 1));
		if (!pointer[content_tokens])
		{
			for (indx -= 1; indx >= 0; indx--)
				free(pointer[indx]);
			free(pointer);
			return (NULL);
		}

		for (content_letters = 0; content_letters < letters; content_letters++)
		{
			pointer[content_tokens][content_letters] = line[indx];
			indx++;
		}

		pointer[content_tokens][content_letters] = '\0';
	}
	pointer[content_tokens] = NULL;
	pointer[content_tokens + 1] = NULL;

	return (pointer);
}
