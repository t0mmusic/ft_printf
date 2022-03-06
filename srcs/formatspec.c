/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:37:12 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/03 10:05:13 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Gets the allocated strings ready for final modifications by 
 * breaking them into the correct catagories */

char	*formatstr(t_specs *s, char *s2)
{
	if (s->format == 's')
		return (strprec(s, s2));
	else if (s->format == 'x' || s->format == 'X' || s->format == 'p')
		return (hexprec(s, s2));
	else
		return (nbrprec(s, s2));
}

/* A list of valid print types that are valid in printf.
 * This list includes types that are not handled by this
 * project but are used by the real printf. */

int	formatcheck(char c)
{
	if (c == 'c' || c == 's' || c == 'n' || c == 'd'
		|| c == 'i' || c == 'o' || c == 'x'
		|| c == 'X' || c == 'p' || c == 'f'
		|| c == 'u' || c == 'G' || c == 'g'
		|| c == 'e' || c == 'E' || c == '%' || c == 'r')
		return (c);
	return (0);
}

/* A list of all format specifiers that can be used to
 * modify the final output. This list includes types
 * that are not handled by this project but are used 
 * by the real printf. */

int	flagcheck(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#'
		|| c == '0' || c == '*' || c == '.'
		|| c == 'l' || c == 'L' || c == 'h')
		return (c);
	if (ft_isdigit(c))
		return (c);
	return (0);
}

/* Attemps to find a valid print type. If a non-valid
 * character is encountered before a type is found,
 * it will return the string up to the last valid
 * character */

char	*paramaterfill(char *s)
{
	int		i;

	i = 0;
	while (s[i] && !formatcheck(s[i]))
	{
		if (!flagcheck(s[i]))
			return (ft_substr(s, 0, i + 1));
		i++;
	}
	return (ft_substr(s, 0, i + 1));
}

/* Creates a string containing everything from '%' to
 * a valid print type or the null terminator */

int	formatspec(const char *c, t_specs *s, va_list v, int *count)
{
	char	*s1;
	int		len;

	if (formatcheck(c[0]) && c[0] != 'r')
	{
		*count += basic_print(c[0], v);
		return (1);
	}
	s1 = paramaterfill((char *) c);
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	flagfill(s, s1);
	if (!formatcheck(s1[len - 1]))
	{
		free(s1);
		return (formatnull(c, s, len, count));
	}
	s->format = s1[len - 1];
	free(s1);
	return (putnewstr(s, v, count, len));
}
