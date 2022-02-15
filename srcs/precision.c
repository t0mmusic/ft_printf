/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:12:47 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/15 13:58:14 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	charcheck(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	charprec(t_specs *s, char *str, int *count)
{
	char	*add;
	int		zero;

	zero = 0;
	if (!str[0])
	{
		*count += 1;
		zero++;
	}
	if (s->width > 1)
	{
		add = ft_calloc(sizeof(*add), s->width + 1);
		if (s->zero && !s->minus)
			strfill(add, '0', s->width - 1);
		else
			strfill(add, ' ', s->width - 1);
		if (s->minus)
			str = freejoin(str, add);
		else
			str = freejoin(add, str);
	}
	if (zero && s->minus)
		ft_putchar_fd(0, 1);
	ft_putstr_fd(str, 1);
	free(str);
	*count += ft_strlen(str);
	if (zero && !s->minus)
		ft_putchar_fd(0, 1);
}

char	*nbrprec(t_specs *s, char *str)
{
	char	*add;
	int		len;

	len = ft_strlen(str);
	if (s->precision == -1 && !ft_atoi(str))
		str[0] = 0;
	if (s->precision > len)
	{
		add = ft_calloc(sizeof(*add), (s->precision - len) + 1);
		strfill(add, '0', s->precision - len);
		str = freejoin(add, str);
	}
	str = nbrwidth(s, str);
	return (str);
}

char	*strprec(t_specs *s, char *str)
{
	int		len;
	char	*tmp;

	if (s->precision == -1)
		str[0] = 0;
	len = ft_strlen(str);
	if (s->precision < len && s->precision)
	{
		tmp = str;
		str = ft_substr(str, 0, s->precision);
		free(tmp);
	}
	str = strwidth(s, str);
	return (str);
}

char	*hexprec(t_specs *s, char *str)
{
	int		len;
	char	*add;

	if (s->precision == -1 && !ft_atoi(str))
		str[0] = 0;
	len = ft_strlen(str);
	if (s->precision > len)
	{
		add = ft_calloc(sizeof(*add), (s->precision - len) + 1);
		strfill(add, '0', s->precision - len);
		str = freejoin(add, str);
	}
	if (s->format == 'p' || (!charcheck(str, '0') && s->pound))
		str = freejoin(ft_strdup("0x"), str);
	str = hexwidth(s, str);
	return (str);
}
