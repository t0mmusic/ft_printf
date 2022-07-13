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
LIBFT = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iheaders -I . -c

RM = rm -f

SRCS = srcs/basic_print.c srcs/character_handle.c srcs/formatspec.c \
	   srcs/formatspec_extra.c srcs/ft_printf.c srcs/string_handle.c \
	   srcs/nbr_prec_width.c srcs/setnbr.c srcs/radix_print.c

OBJ_DEST = mv *.o srcs

OBJS = $(SRCS:.c=.o)

LIBFT_MSG = echo "libft archive compiling..."
LIBFT_CLEAN_MSG = echo "removing libft object files"
LIBFT_FCLEAN_MSG = echo "removing libft archive"
PRINTF_CLEAN_MSG = echo "removing printf object files"
PRINTF_FCLEAN_MSG = echo "removing printf archive"
PRINTF_MSG = echo "printf archive compiling..."
COMPLETE_MSG = echo "printf archive ready!"

all: $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(CFLAGS) $(SRCS) >/dev/null
	@$(PRINTF_MSG)
	@$(OBJ_DEST) >/dev/null
	@ar rcs $(NAME) $(OBJS) >/dev/null
	@$(COMPLETE_MSG)

bonus: $(NAME)

$(LIBFT):
	if [ ! -d "libft/" ]; then\
		git clone https://github.com/t0mmusic/libft.git libft; \
	fi
	@$(LIBFT_MSG)
	@$(MAKE) bonus -C ./libft >/dev/null
	@cp libft/libft.a $(NAME) >/dev/null

clean:
	@$(MAKE) clean -C ./libft >/dev/null
	@$(LIBFT_CLEAN_MSG)
	@$(RM) $(OBJS) >/dev/null
	@$(PRINTF_CLEAN_MSG)

fclean: clean
	@$(MAKE) fclean -C ./libft >/dev/null
	@$(LIBFT_FCLEAN_MSG)
	@$(RM) $(NAME) >/dev/null
	@$(PRINTF_FCLEAN_MSG)

re: fclean all

.PHONY: all clean fclean re
