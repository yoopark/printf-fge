/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_conversion_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:46:50 by yopark            #+#    #+#             */
/*   Updated: 2021/01/17 23:46:50 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h"

/* warning: ' ' flag (is) ignored with '+' flag in gnu_printf format('+' > ' ')
   warning: '0' flag (is) ignored with '-' flag in gnu_printf format('-' > '0') */
static const char 	*set_flag(t_conversion_info *conversion_info_ptr, const char *str)
{
	while (*str == ' ' || *str == '+' || *str == '0' || *str == '-')
	{
		switch (*str)
		{
			case '+':
				if (!conversion_info_ptr->flag_sign || conversion_info_ptr->flag_sign == ' ')
					conversion_info_ptr->flag_sign = '+';
				break ;
			case ' ':
				if (!conversion_info_ptr->flag_sign)
					conversion_info_ptr->flag_sign = ' ';
				break ;
			case '-':
				if (!conversion_info_ptr->flag_alignment || conversion_info_ptr->flag_alignment == '0')
					conversion_info_ptr->flag_alignment = '-';
				break ;
			case '0':
				if (!conversion_info_ptr->flag_alignment)
					conversion_info_ptr->flag_alignment = '0';
				break ;
		}
		++str;
	}
	return (str);
}

static const char 	*set_min_width(t_conversion_info *conversion_info_ptr, const char *str, \
									va_list argument_ptr)
{
	if (*str == '*')
	{
		conversion_info_ptr->min_width = va_arg(argument_ptr, int);
		++str;
	}
	else
	{
		while (ft_isdigit(*str))
		{
			conversion_info_ptr->min_width *= 10;
			conversion_info_ptr->min_width += *str - '0';
			++str;
		}
	}
	return (str);
}

static const char 	*set_precision(t_conversion_info *conversion_info_ptr, const char *str, \
										va_list argument_ptr)
{
	if (*str == '*')
	{
		conversion_info_ptr->precision = va_arg(argument_ptr, int);
		++str;
	}
	else
	{
		while (ft_isdigit(*str))
		{
			conversion_info_ptr->precision *= 10;
			conversion_info_ptr->precision += *str - '0';
			++str;
		}
	}
	return (str);
}

static void			change_conversion_info_values(t_conversion_info *conversion_info_ptr)
{
	if (conversion_info_ptr->min_width < 0)
	{
		if (!conversion_info_ptr->flag_alignment || conversion_info_ptr->flag_alignment == '0')
			conversion_info_ptr->flag_alignment = '-';
		if (conversion_info_ptr->min_width == __INT32_MAX__ * (-1) - 1)
			exit(-1); // 이후 total struct 만들어서 argument_ptr, return_value, is_error 집어넣기! exit 사용하지 말기
		conversion_info_ptr->min_width = -conversion_info_ptr->min_width;
	}
	if (conversion_info_ptr->precision < 0)
	{
		conversion_info_ptr->have_precision = FALSE;
		conversion_info_ptr->precision = 0;
	}
	if (!conversion_info_ptr->have_precision) // because we only handle specifier f, g, and e.
	{
		conversion_info_ptr->have_precision = TRUE;
		conversion_info_ptr->precision = 6;
	}
}

void				set_conversion_info(t_conversion_info *conversion_info_ptr, \
											const char *str, va_list argument_ptr)
{
	++str;
	str = set_flag(conversion_info_ptr, str);
	if (ft_isdigit(*str) || *str == '*')
	{
		conversion_info_ptr->have_min_width = TRUE;
		str = set_min_width(conversion_info_ptr, str, argument_ptr);
	}
	if (*str == '.')
	{
		++str;
		conversion_info_ptr->have_precision = TRUE;
		str = set_precision(conversion_info_ptr, str, argument_ptr);
	}
	if (!conversion_info_ptr->have_precision || conversion_info_ptr->precision < 0 || conversion_info_ptr->min_width < 0)
		change_conversion_info_values(conversion_info_ptr);
	conversion_info_ptr->specifier = *str;
}
