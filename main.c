/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:59:15 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/01 16:44:31 by jbrown           ###   ########.fr       */
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

	i = ft_printf("Mine: %p\n", s1);
	j = printf("Real: %p\n", s1);
	printf("Mine: %i, Real: %i\n", i, j);
	return (0);
}
