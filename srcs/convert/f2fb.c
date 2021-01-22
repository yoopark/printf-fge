/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f2fb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 04:12:02 by yopark            #+#    #+#             */
/*   Updated: 2021/01/18 04:12:02 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fge_internal.h"

// https://zanim.tistory.com/entry/Float-Char-%EB%B0%B0%EC%97%B4-byte%ED%98%95%ED%83%9C%EB%A1%9C-bit%EC%97%B0%EC%82%B0%ED%95%98%EC%97%AC-%EB%B3%80%ED%99%98
// 바이트 별로 따로 옮겨주는 이유가 있지 않을까?
// 이렇게 쉽게 해도 되나?

float_bits		f2fb(float f)
{
	return (*(float_bits*)&f);
}

float			fb2f(float_bits fb)
{
	return (*(float*)&fb);
}
