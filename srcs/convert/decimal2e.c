/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	decimal2e.c
*/

#include "printf_fge_internal.h"

char		*decimal2e(SConversion *conversion_info, char *decimal)
{
	(void)conversion_info;
	printf("%s\n", decimal);
	return _strdup("");
}