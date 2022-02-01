/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:06:40 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/01 16:44:22 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

int	negcheck(long long int n, int count)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
		count += 1;
	}
	ft_putnbr(n);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
