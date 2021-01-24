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
	printf_fge("%020.5fhello\n", -9.999999f);
	printf("%020.5fhello\n", -9.999999f);
	return 0;
}