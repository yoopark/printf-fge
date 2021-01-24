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
	printf_fge("%020.100fhello\n", 12.345f);
	printf("%020.100fhello\n", 12.345f);
	return 0;
}