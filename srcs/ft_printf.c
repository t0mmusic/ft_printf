/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:12:06 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 13:32:34 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* initiates the final string, send it off for modification,
 * prints the final result and return the character count */

int	putnewstr(t_specs *s, va_list v, int *count, int len)
{
	char	*s2;

	s2 = printtype(s->format, v);
	if (!s2)
		return (0);
	if (s->format == 'c' || s->format == '%')
	{
		charprec(s, s2, count);
		return (len);
	}
	s2 = formatstr(s, s2);
	ft_putstr_fd(s2, 1);
	*count += ft_strlen(s2);
	free(s2);
	return (len);
}

/* initialises the structure that keeps track
 * of modifiers for the final output.*/

void	specinit(t_specs *s)
{
	s->format = 0;
	s->width = 0;
	s->precision = 0;
	s->space = 0;
	s->zero = 0;
	s->pound = 0;
	s->plus = 0;
	s->minus = 0;
}

/*  used frequently to reallocate a string
 *  without causing memory leaks */

char	*freejoin(char *s1, char *s2)
{
	char	*t1;
	char	*t2;

	t1 = s1;
	t2 = s2;
	s2 = ft_strjoin(s1, s2);
	free(t1);
	free(t2);
	return (s2);
}

/* determines the print type of the final output. */

char	*printtype(char c, va_list v)
{
	if (c == 'd' || c == 'i')
		return (ft_neghandle(va_arg(v, int)));
	if (c == 'u')
		return (ft_nbrtoa(va_arg(v, unsigned int), 10));
	if (c == 'x' || c == 'X')
		return (ft_nbrtoa(va_arg(v, unsigned int), 16));
	if (c == 'p')
		return (ft_nbrtoa(va_arg(v, unsigned long), 16));
	if (c == 'o')
		return (ft_nbrtoa(va_arg(v, unsigned int), 8));
	if (c == 's')
		return (strhandle(v));
	if (c == 'c')
		return (chartostr(va_arg(v, int)));
	if (c == '%')
		return (chartostr('%'));
	if (c == 'r')
		return (radix_print(v));
	return (NULL);
}

/* Initialises the format structure, prints characters from the
 * string and keeps a running total of characters printed */

int	ft_printf(const char *str, ...)
{
	t_specs	s;
	int		i;
	int		count;

	va_start(s.arg, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		specinit(&s);
		if (str[i] == '%' && str[i++])
			i += formatspec(&str[i], &s, s.arg, &count);
		if (str[i] && str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			i++;
			count++;
		}
	}
	va_end(s.arg);
	return (count);
}
