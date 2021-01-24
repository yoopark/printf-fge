/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 08:03:12 by yopark            #+#    #+#             */
/*   Updated: 2021/01/17 08:03:12 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FGE_INTERNAL_H
# define PRINTF_FGE_INTERNAL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include <stdio.h> // for debugging

# define TRUE		1
# define FALSE		0

# define BIAS		0x7f

extern size_t		g_return_value;

# ifndef FLOAT_BITS
#  define FLOAT_BITS

typedef unsigned	float_bits;

float_bits		f2fb(float f);
float			fb2f(float_bits fb);

# endif

typedef unsigned char			byte;
typedef unsigned char			*byte_pointer;
typedef const unsigned char		*const_byte_pointer;
typedef int						t_bool; // I will use TRUE/FALSE in this return_type.

/*	printf 요소 분석
	기준 : printf("The rate is %+10.2f\n", 0.1234);

	The rate is %+10.2f\n	-> format string(format_str)
	%+10.2f					-> conversion string(conversion_str)
	+						-> flag(flag)
	10						-> field minimum width(min_width)
	2						-> precision(precision)
	f						-> conversion specifier(specifier)

	출처 : https://linux.die.net/man/3/printf */

typedef struct			s_conversion_info
{
	char				flag_sign;
	char				flag_alignment;
	int					min_width;
	t_bool				have_min_width;
	int					precision;
	t_bool				have_precision;
	char				specifier;
}						t_conversion_info;

typedef struct			s_float
{
	unsigned			sign;
	unsigned			exponent;
	unsigned			fraction;
}						t_float;

typedef struct			s_bigint
{
	t_bool				sign;
	unsigned			*arr;
	size_t				len;
}						t_bigint;

void			set_conversion_info(t_conversion_info *conversion_info_ptr, \
										const char *str, va_list argument_ptr);

void			print_specifier_f(t_conversion_info *conversion_info_ptr, float_bits fb);
void			print_specifier_g(t_conversion_info *conversion_info_ptr, float_bits fb);
void			print_specifier_e(t_conversion_info *conversion_info_ptr, float_bits fb);

/* functions in utils.c */
t_bool			ft_isdigit(char c);
void			ft_bzero(void *ptr, size_t n);
size_t			ft_strlen_to_char(const char *str, char c);
void			ft_putstr_with_len(const char *str, size_t len);
void			ft_putchar(const char c);
void			*ft_calloc(size_t cnt, size_t per);
unsigned		*ft_unsigneddup(unsigned *arr, size_t len);

t_float			fb2struct(float_bits fb);
float_bits		struct2fb(t_float float_struct);

u_int32_t		add_binary(u_int32_t u1, u_int32_t u2);
u_int64_t		add_binary64(u_int64_t u1, u_int64_t u2);
u_int32_t		subtract_binary(u_int32_t u1, u_int32_t u2);
u_int64_t		subtract_binary64(u_int64_t u1, u_int64_t u2);
u_int64_t		multiply_binary(u_int32_t u1, u_int32_t u2);
u_int64_t		divide_binary64(u_int64_t dividend, u_int64_t divisor);
u_int32_t		round_to_even_binary(u_int32_t u, unsigned bits);
u_int64_t		round_to_even_binary64(u_int64_t u, unsigned bits);
float_bits		multiply_float_bits(float_bits fb1, float_bits fb2);
unsigned		calculate_digit(u_int32_t u);
unsigned		calculate_digit64(u_int64_t u);

t_bigint		*create_bigint(t_bool sign, unsigned *arr, size_t len);
t_bigint		*right_shift_bigint(t_bigint *bi, unsigned n);
t_bigint		*left_shift_bigint(t_bigint *bi, unsigned n);
byte			extract_bit_from_unsigned(unsigned u, unsigned n);
int				ft_bigint_cmp(t_bigint *bi1, t_bigint *bi2);
t_bigint		*subtract_bigint(t_bigint *bi1, t_bigint *bi2);
t_bigint		*truncate_bigint(t_bigint *bi);

t_bigint		*struct2bigint(t_float float_struct);
t_float			bigint2struct(t_bigint *bi);
char			*bigint2str(t_bigint *bi);

void	show_bigint(t_bigint *bi);

#endif
