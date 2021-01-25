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
	printf_fge("%020.5ghello\n",0.000123f);
	printf("%020.5ghello\n", 0.000123f);
	return 0;
}