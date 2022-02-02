/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:59:15 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/02 14:07:33 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

int	main(int ac, char **av)
{
	char	s1[] = "Hello";
	char	s2[] = "";
	char	c = 'K';
	int		i;
	int		j;

	i = ft_printf("Mine: %%%c %%%x %%%s\n", c, s1, s1, 123);
	j = printf("Real: %%%c %%%x %%%s\n", c, s1, s1, 123);
	printf("Mine: %i, Real: %i\n", i, j);
	return (0);
}
