/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fb2struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:33:47 by yopark            #+#    #+#             */
/*   Updated: 2021/01/19 18:33:47 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_printf_fge_internal.h"

t_float		fb2struct(float_bits fb)
{
	t_float		return_value; // 얘는 왜 malloc으로 안해?

	return_value.sign = fb >> 31;
	return_value.exponent = fb >> 23 & 0xFF;
	return_value.fraction = fb & 0x7FFFFF;
	return (return_value);
}

float_bits	struct2fb(t_float float_struct)
{
	return ((float_struct.sign << 31) | (float_struct.exponent << 23) | float_struct.fraction);
}
