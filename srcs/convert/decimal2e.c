/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	decimal2e.c
*/

#include "printf_fge_internal.h"

static void		movePoint(char *decimal, int offset);

static char		*getEStr(int e);

char			*decimal2e(SConversion *conversion_info, bool sign, char *decimal)
{
	char		*return_str;

	int			point_idx = (int)_strlen_to_charset(decimal, ".");
	int			target_idx = (int)_strlen_to_charset(decimal, "123456789") + 1;
	int			e = point_idx - target_idx;
	char		*e_str;

	if (decimal[0] == '0')
		++e;
	if (target_idx == (int)_strlen(decimal) + 1) {
		e = 0;
		/* Pass in case of 0.0 */
	} else 
		movePoint(decimal, e);

	char *_tmp = decimal;
	decimal = _ltrim(decimal, '0');
	free(_tmp);
	if (decimal[0] == '.') {
		_tmp = decimal;
		decimal = _strjoin("0", decimal);
		free(_tmp);
	}

	decimal = decimal2f(conversion_info, sign, decimal);
	e_str = getEStr(e);
	if (!e_str)
		return NULL;
	return_str = _strjoin(decimal, e_str);
	return return_str;
}

static void		movePoint(char *decimal, int offset)
{
	char		*point_pos = _strchr(decimal, '.');

	if (offset == 0)
		return ;
	else if (offset > 0) {
		for (int _ = 0 ; _ < offset ; ++_) {
			_swap_char(point_pos, point_pos - 1);
			--point_pos;
		}
	} else {
		for (int _ = 0 ; _ < -offset ; ++_) {
			_swap_char(point_pos, point_pos + 1);
			++point_pos;
		}
	}
}

static char		*getEStr(int e)
{
	char		*return_str;
	size_t		len = _strlen("e+00");

	if (!(-99 <= e && e <= 99))
		++len;
	return_str = _calloc(len + 1, sizeof(char));
	if (!return_str)
		return NULL;
	return_str[0] = 'e';
	return_str[1] = e >= 0 ? '+' : '-';
	if (e < 0)
		e = -e;
	if (len == _strlen("e+000")) {
		return_str[2] = _to_digit(e / 100);
		e -= e / 100 * 100;
		return_str[3] = _to_digit(e / 10);
		e -= e / 10 * 10;
		return_str[4] = _to_digit(e);
	} else {
		return_str[2] = _to_digit(e / 10);
		e -= e / 10 * 10;
		return_str[3] = _to_digit(e);
	}
	return return_str;		
}