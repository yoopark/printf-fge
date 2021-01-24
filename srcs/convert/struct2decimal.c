/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	struct2decimal.c
*/

#include "printf_fge_internal.h"

static bool		getBitFromUnsigned(unsigned u, unsigned n);

/* Decimal Point = 소수 부분 */
static char		*addDecimalPointStr(const char *s1, const char *s2);

static char		*multiplyDecimalPointStr(const char *s1, int n);

static char		*getUntilFraction(unsigned fraction)
{

}

char			*struct2decimal(SFloat *sf)
{
	char		*until_fraction;
	char		*until_exponent;
	char		*until_sign;

	until_fraction = getUntilFraction(sf->fraction);
	
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

	return_str = (char*)_calloc(len + 1, sizeof(char));
	if (!return_str)
		return NULL;
	for (size_t i = len - 1 ; i != (size_t)-1 ; --i) {
		n1 = (i >= _strlen(s1)) ? 0 : _to_nbr(s1[i]);
		n2 = (i >= _strlen(s2)) ? 0 : _to_nbr(s1[i]);
		n = n1 + n2;
	}
}

static char		*multiplyDecimalPointStr(const char *s1, int n)
{
	if (!(1 <= n && n <= 9))
		return NULL;
	
}
