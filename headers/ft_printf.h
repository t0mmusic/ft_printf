/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:20:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/14 17:18:26 by jbrown           ###   ########.fr       */
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
int		nbrcount(size_t n, int radix);
void	specinit(t_specs *s);
char	*nbrwidth(t_specs *s, char *str);
char	*strwidth(t_specs *s, char *str);
char	*hexwidth(t_specs *s, char *str);
char	*nbrprec(t_specs *s, char *str);
char	*strprec(t_specs *s, char *str);
char	*hexprec(t_specs *s, char *str);
void	charprec(t_specs *s, char *str, int *count);
char	*freejoin(char *s1, char *s2);
void	strfill(char *str, char c, int len);
char	*paramaterfill(char *s);
int		validitycheck(char *s);
int		flagcheck(char c);
char	*strhandle(va_list v);
char	*chartostr(char	c);
int		formatcheck(char c);

#endif
