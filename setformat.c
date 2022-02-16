/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setformat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:06:09 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 14:14:59 by jbrown           ###   ########.fr       */
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
