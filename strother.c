/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strother.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:06:01 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 14:10:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
