/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	struct2decimal.c
*/

#include "printf_fge_internal.h"

static bool		getBitFromUnsigned(unsigned u, unsigned n);

static char		*addDecimalPointStr(const char *s1, const char *s2);

static char		*multiplyDecimalPointStr(const char *s, int n); // if n == 5 -> * 0.5

static char		*getUntilFraction(unsigned fraction)
{
	char		*unit;
	char		*return_str;

	unit = _strdup("");
	return_str = _strdup("");
	for (unsigned i = 23 - 1 ; i != (unsigned)-1 ; --i) {
		g_tmp = unit;
		unit = multiplyDecimalPointStr(unit, 5);
		free(g_tmp);
		if (getBitFromUnsigned(fraction, i)) {
			g_tmp = return_str;
			return_str = addDecimalPointStr(return_str, unit);
			free(g_tmp);
		}
	}
	if (_strcmp(return_str, "") == 0) {
		free(return_str);
		if (!(return_str = _strdup("0")))
			return NULL;
	}
	return return_str;
}

static char		*multiplyEntireDecimalStr(const char *s, int n);

static char		*getUntilExponent(char *s, unsigned exponent)
{
	char		**map;

	g_tmp = s;
	if (exponent == 0) { // denormalization
		exponent = 1;
		if (!(s = _strjoin("0.", s)))
			return NULL;
	} else {
		if (!(s = _strjoin("1.", s)))
			return NULL;
	}
	free(g_tmp);

	if (exponent > BIAS) {
		for (unsigned _ = 0 ; _ < exponent - BIAS ; ++_) {
			g_tmp = s;
			s = multiplyEntireDecimalStr(s, 2);
			free(g_tmp);
		}
	} else {
		for (unsigned _ = 0 ; _ < BIAS - exponent ; ++_) {
			if (!(map = _split(s, '.')))
				return NULL;
			g_tmp = map[1];
			map[1] = multiplyDecimalPointStr(map[1], 5);
			free(g_tmp);
			if (_strcmp(map[0], "1") == 0) {
				free(map[0]);
				if (!(map[0] = _strdup("0")))
					return NULL;
				g_tmp = map[1];
				map[1] = addDecimalPointStr(map[1], "5");
				free(g_tmp);
			}
			g_tmp = s;
			if (!(s = _strjoin3(map[0], ".", map[1])))
				return NULL;
			free(g_tmp);
			free(map[0]);
			free(map[1]);
			free(map);
		}
	}
	return s;
}

char			*struct2decimal(SFloat *sf)
{
	char		*until_fraction;
	char		*until_exponent;
	char		*until_sign;

	until_fraction = getUntilFraction(sf->fraction);
	until_exponent = getUntilExponent(until_fraction, sf->exponent);
	if (sf->sign) {
		if (!(until_sign = _strjoin("-", until_exponent)))
			return NULL;
	} else {
		if (!(until_sign = _strdup(until_exponent)))
			return NULL;
	}
	// free(until_fraction);	Why error occurs?
	free(until_exponent);
	return until_sign;
}

static bool		getBitFromUnsigned(unsigned u, unsigned n)
{
	return (bool)((u & (0b1 << n)) >> n);
}

static char		*addDecimalPointStr(const char *s1, const char *s2)
{
	char		*return_str;
	size_t		len = _max_size(_strlen(s1), _strlen(s2));
	char		n1, n2, n;
	int			carry = 0;

	return_str = (char*)_calloc(len + 1, sizeof(char));
	if (!return_str)
		return NULL;
	for (size_t i = len - 1 ; i != (size_t)-1 ; --i) {
		n1 = (i >= _strlen(s1)) ? 0 : _to_nbr(s1[i]);
		n2 = (i >= _strlen(s2)) ? 0 : _to_nbr(s2[i]);
		n = n1 + n2 + carry;
		carry = n / 10;
		return_str[i] = _to_digit(n % 10);
	}
	return return_str;
}

static char		*multiplyDecimalPointStr(const char *s, int n)
{
	char		*return_str;
	size_t		len = 1 + _strlen(s);
	int			tmp;
	int			carry = 0;

	if (!(1 <= n && n <= 9))
		return NULL;
	if (_strcmp(s, "") == 0) {
		return_str = (char*)_calloc(2, sizeof(char));
		if (!return_str)
			return NULL;
		return_str[0] = _to_digit((char)n);
		return return_str;
	}
	return_str = (char*)_calloc(len + 1, sizeof(char));
	if (!return_str)
		return NULL;
	for (size_t i = len - 1 ; i != 0 ; --i) {
		tmp = (int)_to_nbr(s[i - 1]) * n + carry;
		carry = tmp / 10;
		return_str[i] = _to_digit((char)(tmp % 10));
	}
	return_str[0] = _to_digit((char)carry);
	return return_str;
}

static char		*multiplyEntireDecimalStr(const char *s, int n)
{
	char		*return_str;
	size_t		len = 1 + _strlen(s);
	int			tmp;
	int			carry = 0;

	if (!(1 <= n && n <= 9))
		return NULL;
	return_str = (char*)_calloc(len + 1, sizeof(char));
	if (!return_str)
		return NULL;
	for (size_t i = len - 1 ; i != 0 ; --i) {
		if (s[i - 1] == '.') {
			return_str[i] = '.';
			continue ;
		}
		tmp = (int)_to_nbr(s[i - 1]) * n + carry;
		carry = tmp / 10;
		return_str[i] = _to_digit((char)(tmp % 10));
	}
	return_str[0] = _to_digit((char)carry);
	if (return_str[0] == '0') {
		g_tmp = return_str;
		if (!(return_str = _strdup(return_str + 1)))
			return NULL;
		// free(g_tmp);		Why error occurs?
	}
	return return_str;
}