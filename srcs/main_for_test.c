/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:19:36 by yopark            #+#    #+#             */
/*   Updated: 2021/01/19 18:19:36 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf_fge.h"

#include "printf_fge_internal.h"

/* main_for_test.c
	2^32개의 float_bits 값 모두에 대하여,
	printf에는 fb2f(float_bits)를 넣고, printf_fge에는 float_bits를 넣어
	%f, %g, %e 모든 경우에 출력이 일치하는지 비교한다. */

/* flag, min_width, precision 첨가 기능은? */

void	show_unsigned(unsigned u)
{
	byte	one_bit;

	for (unsigned i = 31 ; i != -1 ; --i)
	{
		one_bit = (byte)((u & (0b1 << i)) >> i);
		if (one_bit == 0b1)
			printf("1");
		else
			printf("0");
	}
}

void	show_bigint(t_bigint *bi)
{
	if (bi->sign == TRUE)
		printf("-");
	else
		printf("+");
	printf(" ");
	for (size_t i = 0 ; i < bi->len ; ++i)
	{
		show_unsigned(bi->arr[i]);
		printf(" ");
	}
	printf("\n");
}

int		main(void)
{

	printf("%.30f\n", 25.25f);
	printf_fge("%.30f\n", 25.25f);
	return (0);
}
