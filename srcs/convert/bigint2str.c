/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:42:59 by yopark            #+#    #+#             */
/*   Updated: 2021/01/21 16:42:59 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h"

// 리턴값은 몫, bi->arr에는 나머지가 들어간다. 들어올 때 bi가 0이면 return (-1);
static t_bigint		*divide_bigint_ten(t_bigint *bi)
{
	t_bigint	*tmp = bi; // 원래 bi 주소를 저장해놓는 곳. 나중에 리팩토링 필요.
	unsigned	*quotient_arr;
	t_bigint	*quotient;
	unsigned	digit_dividend, digit_divisor, digit_diff;

	if (!(quotient_arr = ft_calloc(bi->len, sizeof(unsigned))))
		return (NULL);
	if (!(quotient = create_bigint(bi->sign, quotient_arr, bi->len)))
		return (NULL);
	digit_dividend = 32 * (bi->len - 1) + calculate_digit(bi->arr[0]);
	digit_divisor = 4;
	if (digit_dividend < digit_divisor)
	{
		free(quotient->arr);
		if (!(quotient->arr = ft_calloc(1, sizeof(unsigned))))
			return (NULL);
		return (quotient);
	}
	digit_diff = digit_dividend - digit_divisor;

	t_bigint	*bi_ten;
	unsigned	*bi_ten_arr;
	
	if (!(bi_ten_arr = ft_calloc(1, sizeof(unsigned))))
		return (NULL);
	bi_ten_arr[0] = 0b1010;
	if (!(bi_ten = create_bigint(FALSE, bi_ten_arr, 1)))
		return (NULL);
	
	while (ft_bigint_cmp(bi, bi_ten) <= 0)
	{
		bi_ten = left_shift_bigint(bi_ten, digit_diff);
		if (ft_bigint_cmp(bi, bi_ten) <= 0)
		{
			quotient->arr[(quotient->len - 1) - digit_diff / 32] |= 0b1 << (digit_diff % 32);
			bi = subtract_bigint(bi, bi_ten);
		}
		--digit_diff;
		free(bi_ten->arr);
		if (!(bi_ten->arr = ft_calloc(1, sizeof(unsigned))))
			return (NULL);
		bi_ten->arr[0] = 10;
		bi_ten->len = 1;
	}
	free(bi_ten_arr);
	free(bi_ten);
	*tmp = *bi; // 나중에 수정 바람.
	return (truncate_bigint(quotient));
}

static size_t	calculate_bigint2str_len(t_bigint *bi)
{
	size_t		return_value;
	t_bigint	*bi_copy;
	unsigned	*arr_copy;

	if (!(arr_copy = ft_unsigneddup(bi->arr, bi->len)))
	{
		/* error */
	}
	if (!(bi_copy = create_bigint(bi->sign, arr_copy, bi->len)))
	{
		/* error */
	}
	return_value = 0;
	while (!(bi_copy->len == 1 && bi_copy->arr[0] == 0))
	{
		if (!(bi_copy = divide_bigint_ten(bi_copy)))
		{
			/* error */
		}
		++return_value;
	}
	return (return_value);
}

// 199 = 19 * 10 + 9 = (1 * 10 + 9) * 10 + 9 = ((0 * 10 + 1) * 10 + 9) * 10 + 9 -> 나머지 계산하면 세자리
// 즉, 이진수 x를 이진수 1010으로 나누어 몫이 0이 되려면 몇번 나누어야되는지 계산하면 이진수만으로 십진수 자릿수를 예측할 수 있다. 
char			*bigint2str(t_bigint *bi)
{
	size_t		len;
	char		*return_str;
	t_bigint	*bi_copy;
	unsigned	*arr_copy;

	len = calculate_bigint2str_len(bi);
	if (!(return_str = (char*)ft_calloc(len + 1, sizeof(char))))
		return (NULL);

	if (!(arr_copy = ft_unsigneddup(bi->arr, bi->len)))
		return (NULL);
	if (!(bi_copy = create_bigint(bi->sign, arr_copy, bi->len)))
		return (NULL);
	for (size_t i = len - 1 ; i != -1 ; --i)
	{
		t_bigint	*bi_tmp;

		bi_tmp = bi_copy;
		if (!(bi_copy = divide_bigint_ten(bi_copy)))
			return (NULL);
		return_str[i] = (char)bi_tmp->arr[0] + '0';
	}
	return (return_str);	
}
