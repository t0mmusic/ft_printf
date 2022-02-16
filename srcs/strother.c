/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strother.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:06:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 14:40:54 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*strhandle(va_list v)
{
	char	*str;
	char	*tmp;

	tmp = va_arg(v, char *);
	if (!tmp)
		return (ft_strdup("(null)"));
	str = ft_strdup(tmp);
	if (!str)
		return (NULL);
	return (str);
}

char	*chartostr(char c)
{
	char	*str;

	str = malloc(sizeof(*str) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

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
