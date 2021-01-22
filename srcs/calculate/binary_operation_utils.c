/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_operation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:17:13 by yopark            #+#    #+#             */
/*   Updated: 2021/01/19 19:17:13 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h" // calculate 전용 header를 만들자

static byte		add_bit(byte b1, byte b2, t_bool is_carried)
{
	byte		return_value;

	ft_bzero(&return_value, sizeof(return_value));
	if (is_carried)
	{
		if ((b1 | b2) == 0b0) // 0 0
			return_value = 0b1;
		else if ((b1 ^ b2) == 0b1) // 0 1 || 1 0
			return_value = 0b10;
		else // 1 1
			return_value = 0b11;
	}
	else
	{
		if ((b1 | b2) == 0b0)
			return_value = 0b0;
		else if ((b1 ^ b2) == 0b1)
			return_value = 0b1;
		else
			return_value = 0b10;
	}
	return (return_value);
}

u_int32_t		add_binary(u_int32_t u1, u_int32_t u2)
{
	u_int32_t	return_value;
	byte		b1, b2;
	t_bool		is_carried;

	ft_bzero(&return_value, sizeof(return_value));
	is_carried = FALSE;
	for (unsigned i = 0 ; i < 32 ; ++i)
	{
		b1 = (byte)((u1 & (0b1U << i)) >> i);
		b2 = (byte)((u2 & (0b1U << i)) >> i);
		b2 = add_bit(b1, b2, is_carried);
		is_carried = ((b2 & 0b10) == 0b10) ? TRUE : FALSE;
		return_value |= ((u_int32_t)(b2 & 0b1)) << i;
	}
	if (is_carried)
	{
		/* overflow */
	}
	return (return_value);
}

u_int64_t		add_binary64(u_int64_t u1, u_int64_t u2)
{
	u_int64_t	return_value;
	byte		b1, b2;
	t_bool		is_carried;

	ft_bzero(&return_value, sizeof(return_value));
	is_carried = FALSE;
	for (unsigned i = 0 ; i < 64 ; ++i)
	{
		b1 = (byte)((u1 & ((u_int64_t)0b1 << i)) >> i);
		b2 = (byte)((u2 & ((u_int64_t)0b1 << i)) >> i);
		b2 = add_bit(b1, b2, is_carried);
		is_carried = ((b2 & 0b10) == 0b10) ? TRUE : FALSE;
		return_value |= ((u_int64_t)(b2 & 0b1)) << i;
	}
	if (is_carried)
	{
		/* overflow */
	}
	return (return_value);
}

u_int32_t		subtract_binary(u_int32_t u1, u_int32_t u2)
{
	return (add_binary(u1, add_binary(~u2, 1U))); // u1 + (-u2)
}

u_int64_t		subtract_binary64(u_int64_t u1, u_int64_t u2)
{
	return (add_binary64(u1, add_binary64(~u2, 1UL)));
}

// https://blog.naver.com/PostView.nhn?blogId=highkrs&logNo=220833955938
u_int64_t		multiply_binary(u_int32_t u1, u_int32_t u2)
{
	u_int64_t	return_value;
	byte		b;

	ft_bzero(&return_value, sizeof(return_value));
	for (unsigned i = 0 ; i < 32 ; ++i)
	{
		b = (byte)((u2 & (0b1 << i)) >> i);
		if (b == 0b1)
			return_value = add_binary64(return_value, (u_int64_t)u1 << i);
	}
	return (return_value);
}

unsigned		calculate_digit(u_int32_t u)
{
	for (unsigned i = 31 ; i != -1 ; --i)
	{
		if ((byte)((u & (0b1 << i)) >> i) == 0b1)
			return (i + 1);
	}
	return (0U);
}

unsigned		calculate_digit64(u_int64_t u)
{
	for (unsigned i = 63 ; i != -1 ; --i)
	{
		if ((byte)((u & ((u_int64_t)0b1 << i)) >> i) == 0b1)
			return (i + 1);
	}
	return (0U);
}

// n << 32 해서 나누면 32자리 몫 생기잖아. -> 소수점은? -> 나중에 BigInt로 바꾸던가 -> 어디까지 계속될줄 알고?
u_int64_t		divide_binary64(u_int64_t dividend, u_int64_t divisor)
{
	unsigned	digit_dividend, digit_divisor, digit_diff;
	u_int64_t	tmp;
	u_int64_t	return_value;

	digit_dividend = calculate_digit64(dividend);
	digit_divisor = calculate_digit64(divisor);
	if (digit_dividend < digit_divisor)
		return (0UL);
	digit_diff = digit_dividend - digit_divisor;
	ft_bzero(&return_value, sizeof(return_value));
	while (dividend >= divisor)
	{
		tmp = divisor << digit_diff;
		if (dividend >= tmp)
		{
			return_value |= ((u_int64_t)0b1 << digit_diff);
			dividend = subtract_binary64(dividend, tmp);
		}
		--digit_diff;
	}
	// dividend -> 나머지
	return (return_value);
}

u_int32_t		round_to_even_binary(u_int32_t u, unsigned bits) // 상위 x bit까지 반올림
{
	byte			one_bit;
	u_int32_t		mask;

	if (bits > 32)
	{
		/* error */
	}
	else if (bits == 32)
		return (u);
	for (unsigned i = 32 - bits - 1 ; i != -1 ; --i)
	{
		one_bit = (byte)((u & (0b1 << i)) >> i);
		if (i == 32 - bits - 1 && one_bit == 0b0)
			break ;
		if (i < 32 - bits - 1 && one_bit == 0b1)
		{
			u = add_binary(u, 0b1 << (32 - bits));
			break ;
		}
		if (i == 0 && one_bit == 0b0)
		{
			if ((byte)(u & (0b1 << (32 - bits)) >> (32 - bits)) == 0b1)
				u = add_binary(u, 0b1 << (32 - bits));
		}
	}
	ft_bzero(&mask, sizeof(mask));
	for (unsigned i = 0 ; i < 32 - bits ; ++i)
		mask |= 0b1 << i;
	mask = ~mask;
	return (u & mask);
}

u_int64_t		round_to_even_binary64(u_int64_t u, unsigned bits) // 상위 x bit까지 반올림
{
	byte			one_bit;
	u_int64_t		mask;

	if (bits > 64)
	{
		/* error */
	}
	else if (bits == 64)
		return (u);
	for (unsigned i = 64 - bits - 1 ; i != -1 ; --i)
	{
		one_bit = (byte)((u & ((u_int64_t)0b1 << i)) >> i);
		if (i == 64 - bits - 1 && one_bit == 0b0)
			break ;
		if (i < 64 - bits - 1 && one_bit == 0b1)
		{
			u = add_binary64(u, (u_int64_t)0b1 << (64 - bits));
			break ;
		}
		if (i == 0 && one_bit == 0b0)
		{
			if ((byte)(u & ((u_int64_t)0b1 << (64 - bits)) >> (64 - bits)) == 0b1)
				u = add_binary64(u, (u_int64_t)0b1 << (64 - bits));
		}
	}
	ft_bzero(&mask, sizeof(mask));
	for (unsigned i = 0 ; i < 64 - bits ; ++i)
		mask |= (u_int64_t)0b1 << i;
	mask = ~mask;
	return (u & mask);
}