/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_prec_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:10:12 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 13:24:56 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* if the precision specifier is greater than the length
 * of the string (number of digits), zeroes are added to the
 * beggining of the string. Also adds a space if the space flag
 * has been set. */

char	*nbrprec(t_specs *s, char *str)
{
	char	*add;
	int		len;

	len = ft_strlen(str);
	if (s->precision == -1 && !ft_atoi(str))
		str[0] = 0;
	if (s->plus && ft_atoi(str) >= 0 && s->format != 'u')
		str = freejoin(ft_strdup("+"), str);
	if (s->precision > len)
	{
		add = ft_calloc(sizeof(*add), (s->precision - len) + 1);
		strfill(add, '0', s->precision - len);
		str = freejoin(add, str);
	}
	if (s->space && !s->plus && ft_atoi(str) >= 0 && s->format != 'u')
		str = freejoin(ft_strdup(" "), str);
	str = nbrwidth(s, str);
	return (str);
}

/* adds zeroes or spaces to the string if width is larger than
 * the length of the string. This also applies the remaining
 * flags. */

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

/* if the precision specifier is greater than the length
 * of the string (number of digits), zeroes are added to the
 * beggining of the string. If applicable, adds "0x" to the
 * beggining of the string. */

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

/* adds zeroes or spaces to the string if width is larger than
 * the length of the string. This also applies the remaining
 * flags and checks to see if the string must be converted to
 * uppercase. */

char	*hexwidth(t_specs *s, char *str)
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
	if (str[0] == '0' && str[1] == '0')
		charmod(&str[1], 'x');
	if (s->format == 'X')
		strupper(str);
	return (str);
}
