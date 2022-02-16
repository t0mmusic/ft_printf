/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:15:13 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 13:13:01 by jbrown           ###   ########.fr       */
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

void	charmod(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == ' ' && str[i])
		i++;
	while(str[i + j] == '0')
		j++;
	if (str[i + j] == c && str[i] == '0')
	{
		str[i + j] = '0';
		str[i] = c;
	}
}

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

char	*freejoin(char *s1, char *s2)
{
	char	*temp;

	temp = s2;
	s2 = ft_strjoin(s1, s2);
	free(s1);
	free(temp);
	return (s2);
}

char	*hexwidth(t_specs *s, char *str)
{
	char	*add;
	int		len;
	int i;

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
	{
		i = -1;
		while (str[++i])
			str[i] = ft_toupper(str[i]);
	}
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
