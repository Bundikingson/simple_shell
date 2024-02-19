#include "S_shell.h"

/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: Header file          */
/*                                                     */
/*              Created by: CelsusK                 */
/*                          Bundi Kingson                  */
/* *************************************************** */

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t k);

/**
 * _strlen - RETURNS STRING length..
 * @s: A POINTER to the CHARS string that are passed as arguments..
 *RETURN: STR length..
 */

int _strlen(const char *u)

{
	int length = 0;

	if (!u)
		return (length);
	for (length = 0; u[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - COPIES STR from src to DEST..
 * @dest: POINTER to the receiving file..
 * @src: POINTER to the file being copied.
 * RETURN: POINTER to dest..
 */

char *_strcpy(char *dest, const char *src)

{
	size_t input;

	for (input = 0; src[input] != '\0'; input++)
		dest[input] = src[input];
	dest[input] = '\0';
	return (dest);
}

/**
 * _strcat - JOINS TWO str..
 * @dest: Pointer to the destination str..
 * @src: Pointer to the source str..
 * RETURN: Pointer to the destination str..
 */

char *_strcat(char *dest, const char *src)

{
	char *dest_file;
	const char *src_file;

	dest_file = dest;
	src_file =  src;

	while (*dest_file != '\0')
		dest_file++;

	while (*src_file != '\0')
		*dest_file++ = *src_file++;
	*dest_file = '\0';
	return (dest);
}

/**
 * _strncat - joins two strings by copying n bytes from source.
 * @dest: Pointer to dest string.
 * @src: Pointer to src string.
 * @k: k bytesto be copied.
 * Return: Pointer to destination string.
 */

char *_strncat(char *dest, const char *src, size_t k)

{
	size_t dest_len = _strlen(dest);
	size_t input;

	for (input = 0; input < k && src[input] != '\0'; input++)
		dest[dest_len + input] = src[input];
	dest[dest_len + input] = '\0';

	return (dest);
}
