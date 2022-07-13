/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:25:59 by jbrown            #+#    #+#             */
/*   Updated: 2022/03/06 21:26:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*	takes two parameters to print a number in any radix. First paramater
	is the radix, second the number. */

char	*radix_print(va_list v)
{
	int		radix;
	size_t	nbr;

	radix = va_arg(v, int);
	nbr = va_arg(v, size_t);
	if (radix < 2)
		return (ft_strdup("Radix must be larger than 1."));
	if (radix > 36)
		return (ft_strdup("Radix must not be larger than 36."));
	return (ft_nbrtoa(nbr, radix));
}
