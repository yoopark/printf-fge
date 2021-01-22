/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 03:55:35 by yopark            #+#    #+#             */
/*   Updated: 2021/01/18 03:55:35 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h"

float_bits	get_power_10(int n)
{
	float_bits	return_value;
	float_bits	fb_ten;

	fb_ten = (float_bits)1092616192; // f2fb(10.0f)
	return_value = (float_bits)1065353216; // f2fb(1.0f)
	for (int i = 0 ; i < n ; ++i)
		return_value = multiply_float_bits(return_value, fb_ten);
	return (return_value);
}

void		print_specifier_f(t_conversion_info *conversion_info_ptr, float_bits fb)
{
	float_bits result = multiply_float_bits(fb, get_power_10(conversion_info_ptr->precision));
	t_float st = fb2struct(result);
	t_bigint *bi = struct2bigint(st);
	char *s = bigint2str(bi);
	printf("%s\n", s);
}
