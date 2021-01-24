/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fge.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 07:58:05 by yopark            #+#    #+#             */
/*   Updated: 2021/01/17 07:58:05 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FGE_H
# define PRINTF_FGE_H

# ifndef FLOAT_BITS
#  define FLOAT_BITS

typedef unsigned	float_bits;

float_bits		f2fb(float f);
float			fb2f(float_bits fb);

# endif

int			printf_fge(const char *format, ... );

#endif