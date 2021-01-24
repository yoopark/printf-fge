/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	printf_fge.c
*/

#include "printf_fge_internal.h"

SGlobal			g_info;
void			*g_tmp;

static void		printAccordingConversionInfo(SConversion *conversion_info)
{
	float_bits		fb;
	SFloat			sf;
	char			*decimal;

	if (conversion_info->specifier != '%') {
		fb = f2fb((float)va_arg(g_info.arg_ptr, double));
		sf = fb2struct(fb);
		decimal = struct2decimal(&sf);
	}
	switch (conversion_info->specifier) {
		case 'f':
			printSpecifierF(conversion_info, decimal);
			break ;
		case 'g':
			printSpecifierG(conversion_info, decimal);
			break ;
		case 'e':
			printSpecifierE(conversion_info, decimal);
			break ;
		default:
			_putchar('%');
	}
}

int				printf_fge(const char *format, ...)
{
	size_t			idx = 0;
	size_t			len_to_next_idx;
	SConversion		conversion_info;

	_bzero(&g_info, sizeof(SGlobal));
	va_start(g_info.arg_ptr, format);
	while (format[idx] != '\0') {
		if (format[idx] == '%') {
			++idx;
			_bzero(&conversion_info, sizeof(SConversion));
			len_to_next_idx = _strlen_to_charset(format + idx, "fge%") + 1;
			setConversionInfo(&conversion_info, format + idx, len_to_next_idx);
			if (g_info.is_error)
				return -1;
			printAccordingConversionInfo(&conversion_info);
		} else {
			len_to_next_idx = _strlen_to_charset(format + idx, "%");
			_putstr_with_len(format + idx, len_to_next_idx);
		}
		idx += len_to_next_idx;
	}
	va_end(g_info.arg_ptr);
	return g_info.return_val;
}