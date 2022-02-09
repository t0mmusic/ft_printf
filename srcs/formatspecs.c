/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatspecs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:39:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/09 16:55:56 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "validity.c"
#include "stringinit.c"

void	specfill(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			s->width = ft_atoi(&str[i]);
			printf("%i\n", ft_atoi(&str[i]));
			printf("%i\n", s->width);
			i += nbrcount(s->width);
		}
		if (str[i] == '.')
		{
			s->precision = ft_atoi(&str[i + 1]);
			i += nbrcount(s->precision);
		}
		if (!str[i + 1])
			s->format = flagcheck(str[i]);
		i++;
	}
}

void	flagfill(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			s->flags.pound = 1;
		if (str[i] == '+')
			s->flags.plus = 1;
		if (str[i] == '-')
			s->flags.minus = 1;
		if (str[i] == '0' && ft_isdigit(str[i + 1])
				&& !ft_isdigit(str[i - 1]))
			s->flags.zero = 1;
		i++;
	}
}

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
		return (ft_strdup(va_arg(v, char *)));
	if (c == 'c')
		return (va_arg(v, char *));
	if (c == '%')
		return ("%");
	return (NULL);
}

char	*formatspec(const char *c, t_specs *s, va_list v)
{
	char	*s1;
	char	*s2;
	char	format;

	s1 = paramaterfill((char *) c);
	if (!s1)
		return (NULL);
	format = s1[ft_strlen(s1) - 1];
	s2 = printtype(format, v);
	flagfill(s, s1);
	return (s2);
}

int	ft_printf(const char *str, ...)
{
	t_specs s;
	int		i;

	va_start(s.arg, str);
	specinit(&s);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i++])
		{
			ft_putstr_fd(formatspec(&str[i], &s, s.arg), 1);
			i++;
		}
		if (str[i] && str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	va_end(s.arg);
	return (0);
}
