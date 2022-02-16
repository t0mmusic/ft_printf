/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:53:03 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 15:09:11 by jbrown           ###   ########.fr       */
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
	while (str[i + j] == '0')
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
	char	*t1;
	char	*t2;

	t1 = s1;
	t2 = s2;
	s2 = ft_strjoin(s1, s2);
	free(t1);
	free(t2);
	return (s2);
}
