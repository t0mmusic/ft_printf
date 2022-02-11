/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:15:13 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/11 17:12:02 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	strfill(char *str, char c, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		str[i] = c;
	str[i] = '\0';
}

char	*freejoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = s2;
	s2 = ft_strjoin(s1, s2);
	free(tmp);
	return (s2);
}

char	*sidejustify(t_specs *s, char *str)
{
	char	*add;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	if (s->width > len)
	{
		add = ft_calloc(sizeof(*add), (s->width - len) + 1);
		if (s->zero && !s->minus && !s->precision)
			strfill(add, '0', s->width - len);
		else
			strfill(add, ' ', s->width - len);
		if (s->minus)
		{
			tmp = str;
			str = ft_strjoin(str, add);
			free(tmp);
		}
		else
			str = freejoin(add, str);
		free(add);
	}
	return (str);
}

char	*hexmod(t_specs *s, char *str)
{
	int		i;

	str = strmod(s, str);
	if ((s->pound && str[0] != '0') || s->format == 'p')
		str = freejoin("0x", str);
	if (s->format == 'X')
	{
		i = -1;
		while (str[++i])
			str[i] = ft_toupper(str[i]);
	}
	return (str);
}

char	*strmod(t_specs *s, char *str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	if (s->precision < len && s->precision)
	{
		tmp = str;
		str = ft_substr(str, 0, s->precision);
		free(tmp);
	}
	str = sidejustify(s, str);
	return (str);
}

char	*nbrmod(t_specs *s, char *str)
{
	char	*add;
	int		len;

	len = ft_strlen(str);
	if (s->precision > len)
	{
		add = ft_calloc(sizeof(*add), (s->precision - len) + 1);
		strfill(add, '0', s->precision - len);
		str = freejoin(add, str);
		len = ft_strlen(str);
		free(add);
	}
	str = sidejustify(s, str);
	if (s->plus && ft_atoi(str) >= 0)
		str = freejoin("+", str);
	if (s->space && !s->plus && ft_atoi(str) >= 0)
		str = freejoin(" ", str);
	return (str);
}
