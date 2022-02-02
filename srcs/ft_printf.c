/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/02 14:02:01 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include "libft.h"

int	strprint(va_list v)
{
	char	*str;

	str = va_arg(v, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	charprint(va_list v)
{
	ft_putchar_fd(va_arg(v, int), 1);
	return (1);
}

int	printtype(const char c, va_list v)
{
	if (c == 'c')
		return (charprint(v));
	if (c == 's')
		return (strprint(v));
	if (c == 'i' || c == 'd')
		return (negcheck(va_arg(v, int)));
	if (c == 'u')
		return (negcheck(va_arg(v, size_t)));
	if (c == 'x')
		return (hexprint(va_arg(v, unsigned int), 0));
	if (c == 'X')
		return (hexprint(va_arg(v, unsigned int), 1));
	if (c == 'p')
		return (hexprint(va_arg(v, unsigned int), 2));
	if (c == '%')
		ft_putchar_fd('%', 1);
	return (0);
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
