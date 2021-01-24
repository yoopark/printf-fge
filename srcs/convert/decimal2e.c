/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	decimal2e.c
*/

#include "printf_fge_internal.h"

char		*decimal2e(SConversion *conversion_info, char *decimal)
{
	char		*return_str;
	bool		sign = false;

	if (decimal[0] == '-') {
		sign = true;
		g_tmp = decimal;
		decimal = _strdup(decimal + 1);
		free(g_tmp);
	}

	/* code */

	if (sign) {
		g_tmp = return_str;
		return_str = _strjoin("-", return_str);
		if (!return_str)
			return NULL;
		free(g_tmp);
	}
	return return_str;
}