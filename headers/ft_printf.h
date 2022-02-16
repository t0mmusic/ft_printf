/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:20:57 by jbrown            #+#    #+#             */
/*   Updated: 2022/02/16 15:09:34 by jbrown           ###   ########.fr       */
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

char	*nbrwidth(t_specs *s, char *str);
char	*strwidth(t_specs *s, char *str);
char	*hexwidth(t_specs *s, char *str);
void	strupper(char *str);
int		charcheck(char *str, char c);
char	*chartostr(char c);
char	*strhandle(va_list v);
void	flagfill(t_specs *s, char *str);
void	setwidth(t_specs *s, char *str);
int		ignoreprec(char *str, int i);
void	setprecision(t_specs *s, char *str);
char	*hexprec(t_specs *s, char *str);
char	*strprec(t_specs *s, char *str);
char	*nbrprec(t_specs *s, char *str);
void	charprec(t_specs *s, char *str, int *count);
char	*charwidth(char	*str, t_specs *s);
char	*printtype(char c, va_list v);
int		ft_printf(const char *str, ...);
int		formatspec(const char *c, t_specs *s, va_list v, int *count);
int		putnewstr(t_specs *s, va_list v, int *count, int len);
char	*formatstr(t_specs *s, char *s2);
int		formatnull(const char *c, t_specs *s, int len, int *count);
char	*paramaterfill(char *s);
int		validitycheck(char *s);
int		flagcheck(char c);
int		formatcheck(char c);
char	*ft_neghandle(long long int n);
char	*ft_nbrtoa(size_t n, int radix);
int		nbrcount(size_t n, int radix);
void	specinit(t_specs *s);
void	strfill(char *str, char c, int len);
void	charmod(char *str, char c);
char	*nbrmod(t_specs *s, char *str);
char	*freejoin(char *s1, char *s2);

#endif
