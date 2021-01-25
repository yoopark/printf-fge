/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	decimal2f.c
*/

#include "printf_fge_internal.h"

static char		*roundToEven(char *decimal, int n);

char			*decimal2f(SConversion *conversion_info, bool sign, char *decimal)
{
	char		*return_str;
	size_t		len = _strlen(_strchr(decimal, '.') + 1);
	char		*zero;

	if (len <= (size_t)conversion_info->precision) {
		zero = _calloc(conversion_info->precision - len + 1, sizeof(char));
		if (!zero)
			return NULL;
		_memset(zero, '0', conversion_info->precision - len);
		if (!(return_str = _strjoin(decimal, zero)))
			return NULL;
		free(zero);
		return return_str;
	}
	return_str = roundToEven(decimal, conversion_info->precision);
	if (!return_str)
		return NULL;
	if (sign) {
		char *_tmp = return_str;
		return_str = _strjoin("-", return_str);
		if (!return_str)
			return NULL;
		free(_tmp);
	}
	return return_str;
}

static char		*roundToEven(char *decimal, int n)
{
	bool		need_rounding = false;
	char		*start = _strchr(decimal, '.') + 1 + n;
	char		*return_str;

	if (*start == '5') {
		for (size_t i = 1 ; start[i] != '\0' ; ++i) {
			if (start[i] != '0') {
				need_rounding = true;
				break ;
			}
		}
		if (!need_rounding)
			need_rounding = *(start - 1) % 2 != 0;
	} else if (*start < '5')
		need_rounding = false;
	else
		need_rounding = true;
	
	return_str = _strndup(decimal, _strlen_to_charset(decimal, ".") + 1 + n);
	if (!return_str)
		return NULL;
	if (need_rounding) {
		++return_str[_strlen(return_str) - 1];
		for (size_t i = _strlen(return_str) - 1 ; i != (size_t)-1 ; --i) {
			if (_to_nbr(return_str[i]) == 10) {
				return_str[i] = '0';
				if (i == 0) {
					char *_tmp = return_str;
					return_str = _calloc(_strlen(return_str) + 2, sizeof(char));
					if (!return_str)
						return NULL;
					_strcpy(return_str + 1, _tmp);
					return_str[0] = '1';
					free(_tmp);
				} else {
					if (return_str[i - 1] == '.')
						++return_str[i - 2];
					else
						++return_str[i - 1];
				}
			}
		}
	}
	return return_str;
}