/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:54:22 by yopark            #+#    #+#             */
/*   Updated: 2021/01/17 14:54:22 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_printf_fge_internal.h"

t_bool		ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (TRUE);
	return (FALSE);
}

void		ft_bzero(void *ptr, size_t n)
{
	byte_pointer	memory_ptr;

	memory_ptr = (byte_pointer)ptr;
	for (size_t i = 0 ; i < n ; ++i)
		memory_ptr[i] = 0;
}

size_t		ft_strlen_to_char(const char *str, char c)
{
	size_t		return_value;

	return_value = 0;
	while (str[return_value] != '\0' && str[return_value] != c)
		++return_value;
	return (return_value);
}

void		ft_putchar(const char c)
{
	write(STDOUT_FILENO, &c, 1);
	++g_return_value;
}

void		ft_putstr_with_len(const char *str, size_t len)
{
	write(STDOUT_FILENO, str, len);
	g_return_value += len;
}

void		*ft_calloc(size_t cnt, size_t per)
{
	void		*return_value;

	if (!(return_value = malloc(cnt * per)))
		return (NULL);
	ft_bzero(return_value, sizeof(return_value));
	return (return_value);
}

unsigned	*ft_unsigneddup(unsigned *arr, size_t len)
{
	unsigned	*return_value;

	if (!(return_value = ft_calloc(len, sizeof(unsigned))))
		return (NULL);
	for (size_t i = 0 ; i < len ; ++i)
		return_value[i] = arr[i];
	return (return_value);
}