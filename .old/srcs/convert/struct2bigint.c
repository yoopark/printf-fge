/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2bigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:00:05 by yopark            #+#    #+#             */
/*   Updated: 2021/01/21 14:00:05 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_printf_fge_internal.h"

t_bigint		*struct2bigint(t_float float_struct)
{
	t_bigint		*return_value;
	unsigned		*new_arr;
	unsigned		real_exponent;

	if (!(new_arr = (unsigned*)ft_calloc(1, sizeof(unsigned))))
		return (NULL);
	new_arr[0] = float_struct.fraction;
	if (!(return_value = create_bigint(float_struct.sign, new_arr, 1)))
		return (NULL);
	if (float_struct.exponent < BIAS)
	{
		return_value->arr[0] = 0;
		return (return_value);
	}
	return_value->arr[0] |= 0b1 << 23;
	real_exponent = float_struct.exponent - BIAS;
	if (real_exponent > 23)
	{
		if (!(return_value = left_shift_bigint(return_value, real_exponent - 23)))
			return (NULL);
	}
	else
	{
		/* 여기서 rounding을 해야 되는거 아니야? 
		예를 들어, 0.328을 소수 둘째자리로 만든다 -> 32.8로 만든다 -> 33으로 만든다 -> 0.33으로 만든다 -> 출력한다 */
		return_value->arr[0] = round_to_even_binary(return_value->arr[0], 32 - 23 + real_exponent); /* overflow라면? */
		if (!(return_value = right_shift_bigint(return_value, 23 - real_exponent)))
			return (NULL);
	}
}

// struct2bigint -> bigint2char* -> char*를 기준으로 소수점, flag, width 처리해도 될듯
// 한마디로 bigint2struct를 써서 굳이 t_float로 바꿔봤자 처리하기 더 힘들어질 뿐이라는 거. 

/*  i2f 함수 중
	rest = i & bits_mask(fbits);
	if (fbits <= 23) {
   		 frac = rest << (23 - fbits); ... 내용을 이해해서 추가하자 */

// https://github.com/DreamAndDead/CSAPP-3e-Solutions/blob/master/chapter2/code/floats/float-f2i.c#L52
t_float			bigint2struct(t_bigint *bi) // t_float -> t_float*
{
	t_float			return_value;
	t_bigint		*tmp_bi;
	unsigned		bits;

	return_value.sign = bi->sign;
	if (bi->len == 1 && bi->arr[0] == 0)
	{
		return_value.exponent = 0;
		return_value.fraction = 0;
		return (return_value);
	}
	bits = (bi->len - 1) * 32 + calculate_digit(bi->arr[0]) - 1;
	return_value.exponent = BIAS + bits;
	if (bits <= 23)
	{
		if (!(tmp_bi = left_shift_bigint(bi, 23 - bits)))
		{
			/* error */
		}
		return_value.fraction = tmp_bi->arr[tmp_bi->len - 1] & 0x7FFFFF;
	}
	else
	{
		if (!(tmp_bi = right_shift_bigint(bi, bits - 23)))
		{
			/* error */
		}
		return_value.fraction = tmp_bi->arr[tmp_bi->len - 1] & 0x7FFFFF;
	}
	return (return_value);
}
