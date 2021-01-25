/*
**	Yongjun Park
**	Created	1/25/2021
**	/Users/chulchul/Desktop/printf-fge/srcs/convert/decimal2g.c
*/

#include "printf_fge_internal.h"

static char		*fInDecimal2g(SConversion *conversion_info, bool sign, char *decimal)
{
	int			original_precision = conversion_info->precision;
	char		*return_str;

	int precision = (int)_strlen_to_charset(decimal, "123456789") - (int)_strlen_to_charset(decimal, ".");
	if (decimal[0] == '0')
		--precision;
	conversion_info->precision += precision;
	if (conversion_info->precision < 0)
		conversion_info->precision = 0;
	return_str = decimal2f(conversion_info, sign, decimal);
	conversion_info->precision = original_precision;

	char *_tmp = return_str;
	return_str = _rtrim(return_str, '0');
	if (!return_str)
		return NULL;
	free(_tmp);
	_tmp = return_str;
	return_str = _rtrim(return_str, '.');
	if (!return_str)
		return NULL;
	free(_tmp);
	return return_str;
}

static char		*eInDecimal2g(SConversion *conversion_info, bool sign, char *decimal)
{
	char		*return_str;
	int			original_precision = conversion_info->precision;

	if (conversion_info->precision >= 1)
		--conversion_info->precision;
	return_str = decimal2e(conversion_info, sign, decimal);
	conversion_info->precision = original_precision;

	char **_map = _split(return_str, 'e');
	if (!_map)
		return NULL;
	char *_tmp = _map[0];
	_map[0] = _rtrim(_map[0], '0');
	if (!_map[0])
		return NULL;
	free(_tmp);
	_tmp = _map[0];
	_map[0] = _rtrim(_map[0], '.');
	if (!_map[0])
		return NULL;
	free(_tmp);
	return_str = _strjoin3(_map[0], "e", _map[1]);
	if (!return_str)
		return NULL;
	free(_map[0]);
	free(_map[1]);
	free(_map);
	return return_str;
}

char			*decimal2g(SConversion *conversion_info, bool sign, char *decimal)
{
	char		*s1, *s2;

	s1 = fInDecimal2g(conversion_info, sign, decimal);
	s2 = eInDecimal2g(conversion_info, sign, decimal);
	if (!s1 || !s2)
		return NULL;
	if (_strlen(s1) > _strlen(s2)) {
		free(s1);
		return s2;
	}
	free(s2);
	return s1;
}