/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatspec_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:33:33 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 13:43:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Used in cases where there is no valid print type specified.
 * In cases where a width has been specified, this will print
 * that number of spaces, or a string of zeroes if the zero flag
 * has been set. It will return the number of printed characters.*/

int	formatnull(const char *c, t_specs *s, int len, int *count)
{
	if (ft_isdigit(c[len + *count - 1]) || (!s->width && !len))
		return (len);
	while (s->width > 1)
	{
		if (s->zero)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		s->width--;
		*count += 1;
	}
	return (len - 1);
}

/* runs through the input string to determine the
 * value of precision. */

void	setprecision(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i] && !s->precision)
	{
		if (str[i] == '.')
		{
			if (formatcheck(str[i + 1]) && str[i + 1] != '%')
					s->precision = -1;
			s->precision += ft_atoi(&str[i + 1]);
			i += nbrcount(s->precision, 10);
		}
		i++;
	}
}

/* used during setwidth, this will ignore numbers following
 * a '.' so that this number is not confused with the width */

int	ignoreprec(char *str, int i)
{
	if (str[i] == '.' || str[i - 1] == '.')
	{
		i++;
		while (ft_isdigit(str[i]) && str[i])
			i++;
	}
	return (i);
}

/* determines the value of width. If multiple valid width strings
 * are found, the last one found is the one used. */

void	setwidth(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = ignoreprec(str, i);
		if (ft_isdigit(str[i]))
		{
			while (str[i] && (str[i] == '0' || !ft_isdigit(str[i])))
				i++;
			if (str[i])
			{
				s->width = ft_atoi(&str[i]);
				i += nbrcount(s->width, 10);
			}
			if (!str[i])
				s->width = 0;
		}
		i++;
	}
	setprecision(s, str);
}

/* sets the flags for format specifiers. */

void	flagfill(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			s->pound = 1;
		if (str[i] == '+')
			s->plus = 1;
		if (str[i] == '-')
			s->minus = 1;
		if (str[i] == ' ')
			s->space = 1;
		if (str[i] == '0' && !ft_isdigit(str[i - 1])
			&& (ft_isdigit(str[i + 1]) || flagcheck(str[i + 1])))
			s->zero = 1;
		i++;
	}
	setwidth(s, str);
}
