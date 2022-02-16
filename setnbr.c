/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:37:08 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 14:40:29 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
