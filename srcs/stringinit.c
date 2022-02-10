/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:03:20 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/10 16:30:55 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	specinit(t_specs *s)
{
	s->format = 0;
	s->width = 0;
	s->precision = 0;
	s->space = 0;
	s->zero = 0;
	s->pound = 0;
	s->plus = 0;
}

int	nbrcount(int i)
{
	int	r;

	r = 0;
	while (i)
	{
		i /= 10;
		r++;
	}
	return (r);
}

char	*ft_nbrtoa(size_t n, int radix)
{
	int		tmp;
	int		digits;
	char	*s;

	tmp = n;
	digits = 0;
	while (tmp)
	{
		tmp /= radix;
		digits++;
	}
	s = malloc(sizeof(*s) * (digits + 1));
	s[digits] = '\0';
	while (--digits > -1)
	{
		if ((n % radix) > 9)
			s[digits] = (n % radix) + 87;
		else
			s[digits] = (n % radix) + '0';
		n /= radix;
	}
	return (s);
}

char	*ft_neghandle(long long int n)
{
	if (n < 0)
	{
		n = -n;
		return (ft_strjoin("-", ft_nbrtoa(n, 10)));
	}
	return (ft_nbrtoa(n, 10));
}
