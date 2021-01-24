/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_operation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:13:08 by yopark            #+#    #+#             */
/*   Updated: 2021/01/20 22:13:08 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_printf_fge_internal.h"

t_bigint		*create_bigint(t_bool sign, unsigned *arr, size_t len)
{
	t_bigint		*return_value;

	if (!(return_value = (t_bigint*)ft_calloc(1, sizeof(t_bigint))))
		return (NULL);
	return_value->sign = sign;
	return_value->arr = arr;
	return_value->len = len;
	return (return_value);
}

byte			extract_bit_from_unsigned(unsigned u, unsigned n) // 가장 중요한 비트 : 31, 덜 중요한 비트 : 0
{
	if (n >= 32)
	{
		/* error */
	}
	return ((byte)((u & (0b1 << n)) >> n));
}

static t_bigint		*right_shift_bigint_once(t_bigint *bi) // 이후 t_bigint *bi, unsigned n 으로 바꾸기
{
	t_bigint		*return_value;
	unsigned		*new_arr;

	if (!bi || !bi->arr)
		return (NULL);
	for (size_t i = bi->len - 1 ; i != -1 ; --i)
	{
		for (unsigned j = 0 ; j < 32 ; ++j)
		{
			if (extract_bit_from_unsigned(bi->arr[i], j) == 0b1)
			{
				if (j == 0 && i != bi->len - 1)
					bi->arr[i + 1] |= 0b1 << 31;
				else if (j != 0)
					bi->arr[i] |= 0b1 << (j - 1);
				bi->arr[i] &= ~(0b1 << j);			
			}
		}
	}
	if (bi->arr[0] == 0 && bi->len != 1)
	{
		if (!(new_arr = (unsigned*)ft_calloc(bi->len - 1, sizeof(unsigned))))
			return (NULL);
		for (size_t i = 1 ; i < bi->len ; ++i)
			new_arr[i - 1] = bi->arr[i];
		if (!(return_value = create_bigint(bi->sign, new_arr, bi->len - 1)))
			return (NULL);
		free(bi->arr);
		free(bi);
	}
	else
		return_value = bi;
	return (return_value);
}

t_bigint			*right_shift_bigint(t_bigint *bi, unsigned n)
{
	t_bigint			*return_value;

	return_value = bi;
	for (unsigned i = 0 ; i < n ; ++i)
	{
		if (!(return_value = right_shift_bigint_once(return_value)))
			return (NULL);
	}
	return (return_value);
}

static t_bigint		*left_shift_bigint_once(t_bigint *bi)
{
	t_bigint		*return_value;
	unsigned		*new_arr;

	if (!bi || !bi->arr)
		return (NULL);
	if (extract_bit_from_unsigned(bi->arr[0], 31) == 0b1)
	{
		if (!(new_arr = (unsigned*)ft_calloc(bi->len + 1, sizeof(unsigned))))
			return (NULL);
		for (size_t i = 0 ; i < bi->len ; ++i)
			new_arr[i + 1] = bi->arr[i];
		if (!(return_value = create_bigint(bi->sign, new_arr, bi->len + 1)))
			return (NULL);
		free(bi->arr);
		free(bi);
	}
	else
		return_value = bi;
	for (size_t i = 0 ; i < return_value->len ; ++i)
	{
		for (unsigned j = 31 ; j != -1 ; --j)
		{
			if (extract_bit_from_unsigned(return_value->arr[i], j) == 0b1)
			{
				if (j == 31)
					return_value->arr[i - 1] |= 0b1;
				else
					return_value->arr[i] |= 0b1 << (j + 1);
				return_value->arr[i] &= ~(0b1 << j);
			}
		}
	}
	return (return_value);
}

t_bigint			*left_shift_bigint(t_bigint *bi, unsigned n)
{
	t_bigint			*return_value;

	return_value = bi;
	for (unsigned i = 0 ; i < n ; ++i)
	{
		if (!(return_value = left_shift_bigint_once(return_value)))
			return (NULL);
	}
	return (return_value);
}

int				ft_bigint_cmp(t_bigint *bi1, t_bigint *bi2)
{
	byte			bi1_byte;
	byte			bi2_byte;

	if (bi1->len < bi2->len)
		return (1);
	else if (bi1->len > bi2->len)
		return (-1);
	for (size_t i = 0 ; i < bi1->len ; ++i)
	{
		for (unsigned j = 31 ; j != -1 ; --j)
		{
			bi1_byte = extract_bit_from_unsigned(bi1->arr[i], j);
			bi2_byte = extract_bit_from_unsigned(bi2->arr[i], j);
			if (bi1_byte < bi2_byte)
				return (1);
			else if (bi1_byte > bi2_byte)
				return (-1);
		}
	}
	return (0);
}

t_bigint			*subtract_bigint(t_bigint *bi1, t_bigint *bi2)
{
	t_bigint		*return_value;
	unsigned		*new_arr;

	if (!bi1 || !bi2 || bi1->len < bi2->len \
			|| ft_bigint_cmp(bi1, bi2) == 1 || bi1->sign || bi2->sign)
		return (NULL);
	if (!(new_arr = (unsigned*)ft_calloc(bi1->len, sizeof(unsigned))))
		return (NULL);
	if (!(return_value = create_bigint(FALSE, new_arr, bi1->len)))
		return (NULL);
	unsigned diff = bi1->len - bi2->len;
	for (size_t i = 0 ; i < return_value->len ; ++i)
	{
		if (bi1->len > bi2->len && i < diff)
		{
			return_value->arr[i] = bi1->arr[i];
			continue ;
		}
		if (bi1->arr[i] >= bi2->arr[i - diff])
			return_value->arr[i] = subtract_binary(bi1->arr[i], bi2->arr[i - diff]);
		else
		{
			for (size_t j = i - 1 ; j != -1 ; --j)
			{
				if (return_value->arr[j] != 0)
				{
					for (size_t k = j ; k != i ; ++k)
						return_value->arr[k] -= 1;
					break ;
				}
			}
			return_value->arr[i] = (u_int32_t)subtract_binary64((u_int64_t)bi1->arr[i] | ((u_int64_t)0b1 << 32), (u_int64_t)bi2->arr[i - diff]);
		}
	}
	return (truncate_bigint(return_value));
}

t_bigint		*truncate_bigint(t_bigint *bi)
{
	unsigned	*tmp;

	while (bi->len != 1 && bi->arr[0] == 0)
	{
		if (!(tmp = ft_calloc(bi->len - 1, sizeof(unsigned))))
			return (NULL);
		for (size_t i = 1 ; i < bi->len ; ++i)
			tmp[i - 1] = bi->arr[i];
		free(bi->arr);
		bi->arr = tmp;
		--bi->len;
	}
	return (bi);
}