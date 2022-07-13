/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:37:08 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 12:37:30 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* converts hexidecimal value to uppercase */

void	strupper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
}

/* if a negative number is input, this function will check
 * to see if the zero flag has been set. If it has, the
 * '-' sign will be replaced with a zero and a new '-' sign
 * will be added to the front of the string. */

char	*nbrmod(t_specs *s, char *str)
{
	int	len;
	int	i;

	i = 0;
	while (str[i] && (!ft_isdigit(str[i]) || str[i] == '0'))
		i++;
	if (ft_atoi(str) < 0 && str[i] && s->format != 'u')
	{
		len = ft_strlen(&str[i]);
		if (s->width < s->precision && len < s->precision)
		{
			str[0] = '0';
			str = freejoin(ft_strdup("-"), str);
		}
	}
	return (str);
}

/* Returns the number of digits in a number. Does not
 * account for leading zeroes. */

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

/* Converts a number into a character string. This radix must
 * be given as a parameter to handle decimal and hexidecimal
 * values. */

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

/* handles negative numbers. This casts input as a long long int
 * so that the nagative limit does not exceed the positive one.
 * Joins a '-' sign after the string has been created. 
 * NOTE: modify if statement */

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
