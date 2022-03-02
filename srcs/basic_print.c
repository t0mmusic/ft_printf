/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 08:54:50 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/03 10:09:39 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Prints a number in the chosen radix. Distinguishes
 * between upper and lower case hexidecimal. */

static int	putnbr_radix(size_t n, size_t radix, char up)
{
	if (!n)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (n >= radix)
	{
		putnbr_radix(n / radix, radix, up);
		putnbr_radix(n % radix, radix, up);	
	}
	if (n < radix)
	{
		if (n > 9)
		{
			if (up == 'X')
				ft_putchar_fd(n + 55, 1);
			else
				ft_putchar_fd(n + 87, 1);
		}
		else
			ft_putchar_fd(n + '0', 1);
	}
	return (nbrcount(n, radix));
}

/* Used as a precheck for integers. If input is negative,
 * it will be flipped to positive and '-' will be printed */

static int	negcheck(long long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
		count++;
	}
	return (putnbr_radix(n, 10, 0) + count);
}

/* Same functionality as putchar, but returns length */

static int	basic_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

/* prints a string or "(null)" if the string is empty,
 * then returns the string length. */

static int	basic_str(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

/* This function is used when no flags are applied to
 * the output. It does not require memory allocation. */

int	basic_print(char c, va_list v)
{
	if (c == 'i' || c == 'd')
		return (negcheck(va_arg(v, int)));
	if (c == 'u')
		return (putnbr_radix(va_arg(v, unsigned int), 10, c));
	if (c == 'x' || c == 'X')
		return (putnbr_radix(va_arg(v, unsigned int), 16, c));
	if (c == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (putnbr_radix(va_arg(v, unsigned long), 16, c) + 2);
	}
	if (c == 'c')
		return (basic_char(va_arg(v, int)));
	if (c == 's')
		return (basic_str(va_arg(v, char *)));
	if (c == '%')
		return (basic_char('%'));
	return (0);
}
