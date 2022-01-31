/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:47:38 by jbrown            #+#    #+#             */
/*   Updated: 2022/01/31 16:41:29 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include <stdarg.h>
#include "libft.h"

void	strprint(va_list v)
{
	ft_putstr_fd(va_arg(v, char *), 1);
}

void	charprint(va_list v)
{
	ft_putchar_fd(va_arg(v, int), 1);
}

void	nbrprint(va_list v)
{
	ft_putnbr_fd(va_arg(v, int), 1);
}

void	printtype(const char c, va_list v, int *i)
{
	if (c == 'c')
		charprint(v);
	 if (c == 's')
		strprint(v);
//	else if (c == 'p')
//		ptrprint(v);
	else if (c == 'i' || c == 'd')
		nbrprint(v);
/*	else if (c == 'u')
		unsignedprint(v);
	else if (c == 'x')
		hexlowprint(v);
	else if (c == 'X')
		hexupprint(v);*/
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		*i++;
	}
}

int	ft_printf(const char *str, ...)
{
	int	i;
	va_list	v;

	va_start(v, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			printtype(str[++i], v, &i);
			i++;
		}
		if (str[i])
			ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(v);
	return (i);
}
