/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:03:20 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/11 14:18:23 by jbrown           ###   ########.fr       */
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

char	*strhandle(va_list v)
{
	char	*str;
	char	*tmp;

	tmp = va_arg(v, char *);
	if (!tmp)
		return (ft_strdup("(null)"));
	str = ft_strdup(tmp);
	if (!str)
		return (NULL);
	return (str);
}

int	nbrcount(size_t n, int radix)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= radix;
		count++;
	}
	return (count);
}

char	*ft_nbrtoa(size_t n, int radix)
{
	int		digits;
	char	*s;

	if (!n)
		return (ft_strdup("0"));
	digits = nbrcount(n, radix);
	s = malloc(sizeof(*s) * (digits + 1));
	if (!s)
		return (NULL);
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
	char	*t1;
	char	*t2;

	if (n < 0)
	{
		n = -n;
		t1 = ft_nbrtoa(n, 10);
		if (!t1)
			return (NULL);
		t2 = t1;
		t1 = ft_strjoin("-", t1);
		free (t2);
		return (t1);
	}
	return (ft_nbrtoa(n, 10));
}
