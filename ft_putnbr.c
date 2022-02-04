/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:06:40 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/04 14:20:28 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(size_t n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	if (n < 10)
		ft_putchar_fd(n + 48, 1);
}

int	nbrcount(size_t n, int radix)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= radix;
		count++;
	}
	return (count);
}

int	hexprint(size_t hex, char c)
{
	int	count;

	count = nbrcount(hex, 16);
	if (c == 'p')
	{
		ft_putstr_fd("0x", 1);
		count += 2;
		c = 'x';
	}
	if (hex >= 16)
	{
		hexprint(hex / 16, c);
		hexprint(hex % 16, c);
	}
	else
	{
		if (hex < 10)
			ft_putchar_fd(hex + 48, 1);
		else if (c == 'x')
			ft_putchar_fd(hex + 87, 1);
		else
			ft_putchar_fd(hex + 55, 1);
	}
	return (count);
}

int	negcheck(long long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
		count++;
	}
	ft_putnbr(n);
	count += nbrcount(n, 10);
	return (count);
}
