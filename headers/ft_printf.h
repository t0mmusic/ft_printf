/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:20:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/10 16:27:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_specs
{
	int		zero;
	int		pound;
	int		plus;
	int		minus;
	va_list	arg;
	char	format;
	int		width;
	int		precision;
	char	space;
}	t_specs;

int		ft_printf(const char *str, ...);
char	*ft_neghandle(long long int n);
char	*ft_nbrtoa(size_t n, int radix);
int		nbrcount(int i);
void	specinit(t_specs *s);
char	*nbrmod(t_specs *s, char *str);
char	*strmod(t_specs *s, char *str);
char	*hexmod(t_specs *s, char *str);
char	*sidejustify(t_specs *s, char *str);
void	strfill(char *str, char c, int len);
char	*paramaterfill(char *s);
int		validitycheck(char *s);
int		flagcheck(char c);
int		formatcheck(char c);

#endif
