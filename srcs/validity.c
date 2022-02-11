/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:05:43 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/11 15:31:15 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*chartostr(char	c)
{
	char	*str;

	if (c == 0)
		ft_putchar_fd(0, 1);
	str = malloc(sizeof(*str) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	formatcheck(char c)
{
	if (c == 'c' || c == 's' || c == 'n' || c == 'd'
		|| c == 'i' || c == 'o' || c == 'x'
		|| c == 'X' || c == 'p' || c == 'f'
		|| c == 'u' || c == 'G' || c == 'g'
		|| c == 'e' || c == 'E' || c == '%')
		return (c);
	return (0);
}

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

int	validitycheck(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !formatcheck(s[i]))
	{
		if (!flagcheck(s[i]))
			return (-1);
		i++;
	}
	if (!formatcheck(s[i]))
		return (-1);
	return (i + 1);
}

char	*paramaterfill(char *s)
{
	int	i;

	i = validitycheck(s);
	if (i < 0)
		return (0);
	return (ft_substr(s, 0, i));
}
