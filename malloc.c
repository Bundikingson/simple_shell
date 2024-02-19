#include "S_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
/**
 * malloc_checked- ASSIGN MEMORY space..
 * @b: amount of MEMORY to be allocated..
 * RETURN: pointer to allocated MEMORY..
 */

void *malloc_checked(unsigned int b)

{
	void *pointer;

	pointer = (void *)malloc(b);
	if (pointer == NULL)
		exit(98);
	return (pointer);

}
