#include "S_shell.h"

/* *************************************************** */
/*                                                     */
/*                                                     */
/*              Function of file: Header file          */
/*                                                     */
/*              Created by: CelsusK                */
/*                          Bundi Kingson                  */
/* *************************************************** */
char *_strchr(char *u, char d);
int _strspn(char *u, char *accept);
int _strcmp(char *u1, char *u2);
int _strncmp(const char *u1, const char *u2, size_t k);

/**
 * _strchr - finds A CHAR in a string..
 * @s: THE STRING being searched..
 * @c: THE CHAR being located..
 * RETURN: THE location of D, ELSE, NULL..
 */

char *_strchr(char *u, char d)

{
	int indx;

	for (indx = 0; u[indx]; indx++)
	{
		if (u[indx] == d)
			return (u + indx);
	}

	return (NULL);
}

/**
 * _strspn - CALCS length of a prefix substring..
 * @s: The STRING..
 * @accept: THE PREFIX to be measured..
 * Return: THE NUM of bytes..
 */

int _strspn(char *u, char *accept)

{
	int bytes = 0;
	int indx;

	while (*u)
	{
		for (indx = 0; accept[indx]; indx++)
		{
			if (*u == accept[indx])
			{
				bytes++;
				break;
			}
		}
		u++;
	}
	return (bytes);
}

/**
 * _strcmp - COMPARES two strings..
 * @u1: STRING1..
 * @u2: STRING2..
 * Return: U1 vs U2 results..
 */

int _strcmp(char *u1, char *u2)

{
	while (*u1 && *u2 && *u1 == *u2)
	{
		u1++;
		u2++;
	}

	if (*u1 != *u2)
		return (*u1 - *u2);

	return (0);
}

/**
 * _strncmp -COMPARE two strings..
 * @u1: POINTER TO a string1..
 * @u2: POINTER TO a string2..
 * @k: The first k bytes of the strings to be COMPARED..
 * RETRUN: -1 if u1 < u2, 0 if u1 = u2, else, 1 if u1 > u2.
 */

int _strncmp(const char *u1, const char *u2, size_t k)

{
	size_t input;

	for (input = 0; u1[input] && u2[input] && input < k; input++)
	{
		if (u1[input] > u2[input])
			return (u1[input] - u2[input]);
		else if (u1[input] < u2[input])
			return (u1[input] - u2[input]);
	}
	if (input == k)
		return (0);
	else
		return (-15);
/*indicates that the COMPARISON WAS NOT completed due to PREMATURE termination*/
}
