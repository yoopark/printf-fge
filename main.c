/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	main.c
*/

/* This file is for testing. */

#include "printf_fge.h"
#include <stdio.h>

int		main(void)
{
	printf_fge("%020fhello\n", 42.4242);
	printf("%020fhello\n", 42.4242);
	return 0;
}