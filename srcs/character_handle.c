/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:51:50 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/28 13:49:57 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* finds the end of a string of spaces and zeroes and replaces.
 * If the input character is found, it then swaps the character
 * at that position with the first zero in the string. */

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

/* converts a single character into a null terminating
 * character array.  */

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

/* checks an array to see if every character in that
 * array are the same as the input */

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

/* checks all of the flags in the format string and applies
 * modifiers based on the flags active. */

void	charprec(t_specs *s, char *str, int *count)
{
	int		zero;

	zero = 0;
	if (!str[0])
	{
		*count += 1;
		zero++;
	}
	if (s->width > 1)
		str = charwidth(str, s);
	if (zero && s->minus)
		ft_putchar_fd(0, 1);
	ft_putstr_fd(str, 1);
	free(str);
	*count += ft_strlen(str);
	if (zero && !s->minus)
		ft_putchar_fd(0, 1);
}

/* Checks the value of the width format specifier. Adds
 * zeroes or spaces to the string depending on the flags
 * set. */

char	*charwidth(char	*str, t_specs *s)
{
	char	*add;

	add = ft_calloc(sizeof(*add), s->width + 1);
	if (s->zero && !s->minus)
		strfill(add, '0', s->width - 1);
	else
		strfill(add, ' ', s->width - 1);
	if (s->minus)
		str = freejoin(str, add);
	else
		str = freejoin(add, str);
	return (str);
}
