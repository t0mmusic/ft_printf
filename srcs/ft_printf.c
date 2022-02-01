/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/01 16:44:26 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include "libft.h"

int	hexprint(unsigned int hex, int up)
{
	if (hex >= 16)
	{
		hexprint(hex / 16, up);
		hexprint(hex % 16, up);
	}
	else
	{
		if (hex < 10)
			ft_putchar_fd(hex + 48, 1);
		else if (up)
			ft_putchar_fd(hex + 55, 1);
		else
			ft_putchar_fd(hex + 87, 1);
	}
	return (1);
}

int	strprint(va_list v)
{
	ft_putstr_fd(va_arg(v, char *), 1);
	return (ft_strlen(va_arg(v, char *)));
}

int	charprint(va_list v)
{
	ft_putchar_fd(va_arg(v, int), 1);
	return (1);
}

int	printtype(const char c, va_list v)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += charprint(v);
	if (c == 's')
		count += strprint(v);
	if (c == 'p')
	{
		ft_putstr_fd("0x", 1);
		count += hexprint(va_arg(v, int), 0) + 2;
	}
	if (c == 'i' || c == 'd')
		count += negcheck(va_arg(v, int), count);
	if (c == 'u')
		count += negcheck(va_arg(v, size_t), count);
	if (c == 'x')
		count += hexprint(va_arg(v, unsigned int), 0);
	if (c == 'X')
		count += hexprint(va_arg(v, unsigned int), 1);
	if (c == '%')
		ft_putchar_fd('%', 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	v;

	va_start(v, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += printtype(str[++i], v);
			i++;
		}
		if (str[i] && str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
		count++;
	}
	va_end(v);
	return (count);
}
