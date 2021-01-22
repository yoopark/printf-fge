/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 03:56:28 by yopark            #+#    #+#             */
/*   Updated: 2021/01/18 03:56:28 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h"

void		print_specifier_e(t_conversion_info *conversion_info_ptr, float_bits fb)
{
	printf("%f\n", fb2f(fb));
}
