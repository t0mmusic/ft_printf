/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:37:52 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 14:00:07 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* replaces everything in a string with a single character
 * input as a parameter. */

void	strfill(char *str, char c, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		str[i] = c;
	str[i] = '\0';
}

/* returns a character array from the variable argument
 * list. If the argument is null, the string "(null)" is
 * returned.  */

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

/* sets the precision of the string as determined by the 
 * format specifier. If the precision is less than the length
 * of the string, the string length is reduced to match the
 * precision.  */

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

/* sets the width of the string as determined by the 
 * format specifier. If the width is larger than the length
 * of the string, zeroes or spaces are added to the beggining
 * of the string. */

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
