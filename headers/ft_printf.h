/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:20:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/09 16:00:17 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef	struct	s_flags
{
	int	zero;
	int	pound;
	int	plus;
	int	minus;
}	t_flags;

typedef	struct	s_specs
{
	va_list	arg;
	char	format;
	t_flags	flags;
	int		width;
	int		precision;
	char	length;
}	t_specs;

void	ft_putnbr(size_t n);
int		hexprint(size_t hex, char c);
int		negcheck(long long int n);
int		ft_printf(const char *str, ...);

#endif
