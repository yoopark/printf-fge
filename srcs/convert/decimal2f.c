/*
**	Yongjun Park
**	Created	2021. 1. 24.
**	decimal2f.c
*/

#include "printf_fge_internal.h"

static char		*round_to_even(char *decimal, int n)
{

}

/*
u_int32_t		round_to_even_binary(u_int32_t u, unsigned bits) // 상위 x bit까지 반올림
{
	byte			one_bit;
	u_int32_t		mask;

	if (n > 32) {

	}
	else if (bits == 32)
		return (u);
	for (unsigned i = 32 - bits - 1 ; i != -1 ; --i)
	{
		one_bit = (byte)((u & (0b1 << i)) >> i);
		if (i == 32 - bits - 1 && one_bit == 0b0)
			break ;
		if (i < 32 - bits - 1 && one_bit == 0b1)
		{
			u = add_binary(u, 0b1 << (32 - bits));
			break ;
		}
		if (i == 0 && one_bit == 0b0)
		{
			if ((byte)(u & (0b1 << (32 - bits)) >> (32 - bits)) == 0b1)
				u = add_binary(u, 0b1 << (32 - bits));
		}
	}
	ft_bzero(&mask, sizeof(mask));
	for (unsigned i = 0 ; i < 32 - bits ; ++i)
		mask |= 0b1 << i;
	mask = ~mask;
	return (u & mask);
}
*/

char			*decimal2f(SConversion *conversion_info, char *decimal)
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
	return_str = round_to_even(decimal, conversion_info->precision);
	if (!return_str)
		return NULL;
	return return_str;
}