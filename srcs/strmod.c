/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:15:13 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/10 16:37:44 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

void	strfill(char *str, char c, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		str[i] = c;
	str[i] = '\0';
}

char	*sidejustify(t_specs *s, char *str)
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
			str = ft_strjoin(str, add);
		else
			str = ft_strjoin(add, str);
		free(add);
	}
	return (str);
}

char	*hexmod(t_specs *s, char *str)
{
	int	i;

	if (s->format == 'X')
	{
		i = -1;
		while (str[++i])
			str[i] = ft_toupper(str[i]);
	}
	if (s->pound || s->format == 'p')
		str = ft_strjoin("0x", str);
	return (str);
}

char	*strmod(t_specs *s, char *str)
{
	int		len;

	len = ft_strlen(str);
	if (s->precision < len && s->precision)
		str = ft_substr(str, 0, s->precision);
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
		str = ft_strjoin(add, str);
		len = ft_strlen(str);
		free(add);
	}
	str = sidejustify(s, str);
	if (s->plus && ft_atoi(str) >= 0)
		str = ft_strjoin("+", str);
	if (s->space && !s->plus && ft_atoi(str) >= 0)
		str = ft_strjoin(" ", str);
	return (str);
}
