# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 10:58:52 by jbrown            #+#    #+#              #
#    Updated: 2022/03/03 10:15:58 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders -I . -c

RM = rm -f

SRCS = srcs/basic_print.c srcs/character_handle.c srcs/formatspec.c \
	   srcs/formatspec_extra.c srcs/ft_printf.c srcs/string_handle.c \
	   srcs/nbr_prec_width.c srcs/setnbr.c srcs/radix_print.c

OBJ_DEST = mv *.o srcs

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	$(MAKE) bonus -C ./libft
	cp libft/libft.a $(NAME)
	$(CC) $(CFLAGS) $(SRCS)
	$(OBJ_DEST)
	ar rcs $(NAME) $(OBJS)

bonus: $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
