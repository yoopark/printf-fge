/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bits_operation_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:19:32 by yopark            #+#    #+#             */
/*   Updated: 2021/01/19 18:19:32 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h"

// https://m.cafe.daum.net/kpucomjjang/D7M4/30?q=D_7_beATEAlUg0&

float_bits		multiply_float_bits(float_bits fb1, float_bits fb2)
{
	t_float			struct1, struct2;
	t_float			return_struct;
	unsigned		tmp_exponent;
	u_int64_t		tmp_fraction;

	struct1 = fb2struct(fb1);
	struct2 = fb2struct(fb2);
	return_struct.sign = struct1.sign ^ struct2.sign;
	tmp_exponent = add_binary(struct1.exponent, struct2.exponent);
	if (tmp_exponent < BIAS)
	{
		/* underflow */
	}
	else if (tmp_exponent > 255 + BIAS)
	{
		/* overflow */
	}
	return_struct.exponent = subtract_binary(tmp_exponent, BIAS);
	if (struct1.exponent != 0)
		struct1.fraction |= 0b1 << 23;
	else
		struct1.exponent += 1;
	if (struct2.exponent != 0)
		struct2.fraction |= 0b1 << 23;
	else
		struct2.exponent += 1;
	tmp_fraction = multiply_binary(struct1.fraction, struct2.fraction);
	if (calculate_digit64(tmp_fraction) > 46 + 1)
	{
		unsigned digit_diff = calculate_digit64(tmp_fraction) - (46 + 1);
		return_struct.exponent += digit_diff; // overfiow 체크 해야함
		tmp_fraction >>= digit_diff;
	}
	return_struct.fraction = (unsigned)((round_to_even_binary64(tmp_fraction, 64 - 23) >> 23) & 0x7FFFFF);
	return (struct2fb(return_struct));
}
