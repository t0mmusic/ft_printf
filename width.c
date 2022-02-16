/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:51:51 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 13:01:09 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	strupper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
}

char	*hexwidth(t_specs *s, char *str)
{
	char	*add;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (s->width > len)
	{
		add = ft_calloc(sizeof(*add), (s->width - len) + 1);
		if (s->zero && !s->minus && !s->precision)
			strfill(add, '0', s->width - len);
		else
			strfill(add, ' ', s->width - len);
		if (s->minus)
			str = freejoin(str, add);
		else
			str = freejoin(add, str);
	}
	if (str[0] == '0' && str[1] == '0')
		charmod(&str[1], 'x');
	if (s->format == 'X')
		strupper(str);
	return (str);
}

char	*strwidth(t_specs *s, char *str)
{
	char	*add;
	int		len;

	len = ft_strlen(str);
	if (s->width > len)
	{
		add = ft_calloc(sizeof(*add), (s->width - len) + 1);
		if (s->zero && !s->minus)
			strfill(add, '0', s->width - len);
		else
			strfill(add, ' ', s->width - len);
		if (s->minus)
			str = freejoin(str, add);
		else
			str = freejoin(add, str);
	}
	return (str);
}

char	*nbrwidth(t_specs *s, char *str)
{
	char	*add;
	int		len;

	len = ft_strlen(str);
	if (s->width > len)
	{
		add = ft_calloc(sizeof(*add), (s->width - len) + 1);
		if (s->zero && !s->minus && !s->precision)
			strfill(add, '0', s->width - len);
		else
			strfill(add, ' ', s->width - len);
		if (s->minus)
			str = freejoin(str, add);
		else
			str = freejoin(add, str);
	}
	if (s->precision || s->zero)
		charmod(str, '-');
	if (s->plus)
		charmod(str, '+');
	if (s->space)
		charmod(str, ' ');
	if (s->format != 'u' && s->precision)
		str = nbrmod(s, str);
	return (str);
}
