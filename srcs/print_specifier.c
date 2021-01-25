/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	print_specifier.c
*/

#include "printf_fge_internal.h"

void		printSpecifier(char type, SConversion *conversion_info, bool sign, char *decimal)
{
	char		*s = NULL;

	switch (type) {
		case 'f':
			s = decimal2f(conversion_info, sign, decimal);
			break ;
		case 'g':
			s = decimal2g(conversion_info, sign, decimal);
			break ;
		case 'e':
			s = decimal2e(conversion_info, sign, decimal);
	}
	if (!s) {
		g_info.is_error = true;
		return ;
	}
	if (s[0] == '-')
		printIncludingSpaces("-", s + 1, conversion_info);
	else
		printIncludingSpaces("+", s, conversion_info);
	free(s);
}