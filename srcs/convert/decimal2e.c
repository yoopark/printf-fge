/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	decimal2e.c
*/

#include "printf_fge_internal.h"

char		*decimal2e(SConversion *conversion_info, char *decimal)
{
	bool		sign = false;

	if (decimal[0] == '-') {
		sign = true;
		g_tmp = decimal;
		decimal = _strdup(decimal + 1);
		free(g_tmp);
	}


	return _strdup("");
}