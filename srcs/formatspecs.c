/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatspecs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:39:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/10 16:31:50 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	specfill(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			s->width = ft_atoi(&str[i]);
			i += nbrcount(s->width);
		}
		if (str[i] == '.' && !s->precision)
		{
			s->precision = ft_atoi(&str[i + 1]);
			i += nbrcount(s->precision);
		}
		if (!str[i + 1])
			s->format = str[i];
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
			s->pound = 1;
		if (str[i] == '+')
			s->plus = 1;
		if (str[i] == '-')
			s->minus = 1;
		if (str[i] == ' ')
			s->space = 1;
		if (str[i] == '0' && ft_isdigit(str[i + 1])
			&& !ft_isdigit(str[i - 1]))
			s->zero = 1;
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

int	formatspec(const char *c, t_specs *s, va_list v, int *count)
{
	char	*s1;
	char	*s2;
	char	format;

	s1 = paramaterfill((char *) c);
	if (!s1)
		return (0);
	format = s1[ft_strlen(s1) - 1];
	s2 = printtype(format, v);
	flagfill(s, s1);
	specfill(s, s1);
	if (s->format == 's')
		s2 = strmod(s, s2);
	else if (s->format == 'x' || s->format == 'X' || s->format == 'p')
		s2 = hexmod(s, s2);
	else
		s2 = nbrmod(s, s2);
	ft_putstr_fd(s2, 1);
	*count += ft_strlen(s2);
	return (ft_strlen(s1));
}

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
