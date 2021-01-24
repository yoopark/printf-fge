/*
**	Yongjun Park
**	Created	2021. 1. 23.
**	set_conversion_info.c
*/

#include "printf_fge_internal.h"

static void		setFlag(SConversion *conversion_info, const char **s)
{
	while (_strchr("+ -0", **s) != NULL) {
		switch (**s) {
			case '+':
				conversion_info->sign_flag = '+';
				break ;
			case ' ':
				if (conversion_info->sign_flag != '+')
					conversion_info->sign_flag = ' ';
				break ;
			case '-':
				conversion_info->alignment_flag = '-';
				break ;
			case '0':
				if (conversion_info->alignment_flag != '-')
					conversion_info->alignment_flag = '0';
		}
		++(*s);
	}
}

static int		getNumberFromDigit(const char **s);

static void		setWidth(SConversion *conversion_info, const char **s)
{
	conversion_info->width = getNumberFromDigit(s);
}

static void		setPrecision(SConversion *conversion_info, const char **s)
{
	conversion_info->precision = getNumberFromDigit(s);
}

static void		setSpecifier(SConversion *conversion_info, const char **s)
{
	if (_strchr("fge%", **s)) {
		conversion_info->specifier = **s;
		++(*s);
	}
}

void			modifyWidth(SConversion *conversion_info);

void			modifyPrecision(SConversion *conversion_info);

void			setConversionInfo(SConversion *conversion_info, const char *s, size_t len)
{
	const char		*original = s;

	// Parse conversion string
	setFlag(conversion_info, &s);
	if (_isdigit(*s) || *s == '*')
		setWidth(conversion_info, &s);
	if (*s == '.') {
		++s;
		conversion_info->have_precision = true;
		setPrecision(conversion_info, &s);
	}
	setSpecifier(conversion_info, &s);

	if (s != original + len) {
		g_info.is_error = true;
		return ;
	}
	if (conversion_info->width < 0)
		modifyWidth(conversion_info);
	if (!conversion_info->have_precision || conversion_info->precision < 0)
		modifyPrecision(conversion_info);
}

static int		getNumberFromDigit(const char **s)
{
	int			n = 0;

	if (**s == '*') {
		n = va_arg(g_info.arg_ptr, int);
		++(*s);
	} else {
		while (_isdigit(**s)) {
			n *= 10;
			n += **s - '0';
			++(*s);
		}
	}
	return n;
}

void			modifyWidth(SConversion *conversion_info)
{
	conversion_info->alignment_flag = '-';
	conversion_info->width = -conversion_info->width;
}

void			modifyPrecision(SConversion *conversion_info)
{
	// conversion_info->have_precision = true;
	conversion_info->precision = 6;	
}