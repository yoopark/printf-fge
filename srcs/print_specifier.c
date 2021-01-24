/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	print_specifier.c
*/

#include "printf_fge_internal.h"

void		printSpecifierE(SConversion *conversion_info, char *decimal)
{
	char		*s;

	s = decimal2e(conversion_info, decimal);
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

void		printSpecifierF(SConversion *conversion_info, char *decimal)
{
	char		*s;

	s = decimal2f(conversion_info, decimal);
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

void		printSpecifierG(SConversion *conversion_info, char *decimal)
{
	char		*s1, *s2, *s;

	s1 = decimal2f(conversion_info, decimal);
	s2 = decimal2e(conversion_info, decimal);
	if (!s1 || !s2) {
		g_info.is_error = true;
		return ;
	}
	if (_strlen(s1) > _strlen(s2)) {
		s = s2;
		free(s1);
	} else {
		s = s1;
		free(s2);
	}
	if (s[0] == '-')
		printIncludingSpaces("-", s + 1, conversion_info);
	else
		printIncludingSpaces("+", s, conversion_info);
	free(s);
}