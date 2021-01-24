/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 07:57:38 by yopark            #+#    #+#             */
/*   Updated: 2021/01/17 07:57:38 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_printf_fge_internal.h"

size_t				g_return_value;

static size_t		get_conversion_str_len(const char *str)
{
	for (size_t return_value = 1 ; str[return_value] != '\0' ; ++return_value)
	{
		if (str[return_value] == 'f' \
				|| str[return_value] == 'g' \
				|| str[return_value] == 'e' \
				|| (return_value == 1 && str[return_value] == '%'))
			return (++return_value);
	}
	return (0);
}

static t_bool		is_valid_conversion_str(const char *str, size_t len)
{
	size_t		idx;

	idx = 1;
	while (str[idx] == ' ' || str[idx] == '+' || str[idx] == '0' || str[idx] == '-')
		++idx;
	if (str[idx] == '*')
		++idx;
	else
	{
		while (ft_isdigit(str[idx]))
			++idx;
	}
	if (str[idx] == '.')
	{
		++idx;
		if (str[idx] == '*')
			++idx;
		else
		{
			while (ft_isdigit(str[idx]))
				++idx;
		}
	}
	if (++idx != len)
		return (FALSE);
	return (TRUE);
}

static void			print_using_conversion_info(t_conversion_info *conversion_info_ptr, \
													va_list argument_ptr)
{
	// printf("flag_sign: %c\n", conversion_info_ptr->flag_sign);
	// printf("flag_alignment: %c\n", conversion_info_ptr->flag_alignment);
	// printf("min_width: %d\n", conversion_info_ptr->min_width);
	// printf("precision: %d\n", conversion_info_ptr->precision);
	// printf("specifier: %c\n", conversion_info_ptr->specifier);

	switch (conversion_info_ptr->specifier)
	{
		case 'f':
			print_specifier_f(conversion_info_ptr, f2fb(va_arg(argument_ptr, double)));
			break ;
			/* warning: ‘float’ is promoted to ‘double’ when passed through ‘...’
				(so you should pass 'doubld' not 'float' to 'va_arg') 
				%f라고 해도 printf에서는 double로 인식하기 때문에 정확도 차이가 발생할 수 있다는 점에 주의! */
		case 'g':
			print_specifier_g(conversion_info_ptr, f2fb(va_arg(argument_ptr, double)));
			break ;
		case 'e':
			print_specifier_e(conversion_info_ptr, f2fb(va_arg(argument_ptr, double)));
			break ;
		default:
			ft_putchar('%');
	}
}

int					printf_fge(const char *format, ... )
{
	size_t				format_idx;
	size_t				len_to_next_format_idx;
	t_conversion_info	conversion_info;
	va_list				argument_ptr;

	format_idx = 0;
	g_return_value = 0;
	va_start(argument_ptr, format);
	while (format[format_idx] != '\0')
	{
		if (format[format_idx] == '%')
		{
			if ((len_to_next_format_idx = get_conversion_str_len(format + format_idx)) == 0)
			{
				va_end(argument_ptr);
				return (-1);
			}
			if (!is_valid_conversion_str(format + format_idx, len_to_next_format_idx))
			{
				va_end(argument_ptr);
				return (-1);
			}
			ft_bzero(&conversion_info, sizeof(conversion_info));
			set_conversion_info(&conversion_info, format + format_idx, argument_ptr);
			print_using_conversion_info(&conversion_info, argument_ptr);
		}
		else
		{
			len_to_next_format_idx = ft_strlen_to_char(format + format_idx, '%');
			ft_putstr_with_len(format + format_idx, len_to_next_format_idx);
		}
		format_idx += len_to_next_format_idx;
	}
	va_end(argument_ptr);
	if (g_return_value > __INT32_MAX__)
		return (-1);
	return ((int)g_return_value);
}
