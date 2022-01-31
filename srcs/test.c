/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:10:04 by jbrown            #+#    #+#             */
/*   Updated: 2022/01/31 14:59:12 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void	test(char *str, ...)
{
	va_list v;

	va_start(v, str);
	printf("%s", va_arg(v, char *));
	printf("%s", va_arg(v, char *));
}

int	main(int ac, char **av)
{
	test("Hello", "world", "How", "Are", "You");
	return (0);
}
