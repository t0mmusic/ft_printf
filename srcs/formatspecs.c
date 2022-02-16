/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatspecs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:39:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 14:35:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	setwidth(t_specs *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' || str[i - 1] == '.')
		{
			i++;
			while (ft_isdigit(str[i]) && str[i])
				i++;
		}
		if (ft_isdigit(str[i]))
		{
			while(str[i] && (str[i] == '0' || !ft_isdigit(str[i])))
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
	return (NULL);
}

int	formatspec(const char *c, t_specs *s, va_list v, int *count)
{
	char	*s1;
	char	*s2;
	int		len;

	s1 = paramaterfill((char *) c);
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	flagfill(s, s1);
	if (!formatcheck(s1[len - 1]))
	{
		s2 = NULL;
		free(s1);
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
	s->format = s1[len - 1];
	s2 = printtype(s->format, v);
	if (!s2)
		return (0);
	free(s1);
	if (s->format == 'c' || s->format == '%')
	{
		charprec(s, s2, count);
		return (len);
	}
	else if (s->format == 's')
		s2 = strprec(s, s2);
	else if (s->format == 'x' || s->format == 'X' || s->format == 'p')
		s2 = hexprec(s, s2);
	else
		s2 = nbrprec(s, s2);
	ft_putstr_fd(s2, 1);
	*count += ft_strlen(s2);
	free(s2);
	return (len);
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
