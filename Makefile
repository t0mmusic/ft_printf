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

NAME = archives/libftprintf.a
LIBFT = libft.a
CC = gcc

RM = rm -rf

SRCS = srcs/basic_print.c srcs/character_handle.c srcs/formatspec.c \
	   srcs/formatspec_extra.c srcs/ft_printf.c srcs/string_handle.c \
	   srcs/nbr_prec_width.c srcs/setnbr.c srcs/radix_print.c

OBJ_DEST = objects
ARCHIVE_DEST = archives
HEADER_DEST = headers
HDR_INCL = $(HEADER_DEST)/inc_headers

CFLAGS = -Wall -Werror -Wextra -I $(HEADER_DEST) -I $(HDR_INCL)

OBJS = $(SRCS:srcs/%.c=objects/%.o)

LIBFT_MSG = echo "libft archive compiling..."
LIBFT_CLEAN_MSG = echo "removing libft object files"
LIBFT_FCLEAN_MSG = echo "removing libft archive"
PRINTF_CLEAN_MSG = echo "removing printf object files"
PRINTF_FCLEAN_MSG = echo "removing printf archive"
PRINTF_MSG = echo "printf archive compiling..."
COMPLETE_MSG = echo "printf archive ready!"

.DELETE_ON_ERROR:

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(PRINTF_MSG)
	@ar rcs $(NAME) $(OBJS) >/dev/null
	@$(COMPLETE_MSG)

bonus: $(NAME)

$(LIBFT):
	@if [ ! -d "libft/" ]; then\
		printf "libft dependency needed. Download now? [y/N]" \
		&& read ans && [ $${ans:-N} = y ] \
		&& git clone https://github.com/t0mmusic/libft.git libft; \
	fi
	@$(LIBFT_MSG)
	@$(MAKE) bonus -C ./libft >/dev/null
	@mkdir -p $(OBJ_DEST)
	@mkdir -p $(ARCHIVE_DEST)
	@mkdir -p $(HDR_INCL)
	@cp libft/libft.a $(NAME) >/dev/null
	@mv libft/*.o $(OBJ_DEST)
	@cp libft/*.h $(HDR_INCL)

objects/%.o: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "Linked source: %s into object: %s\n" $< $@

clean:
	@$(MAKE) clean -C ./libft >/dev/null
	@$(LIBFT_CLEAN_MSG)
	@$(RM) $(OBJS) >/dev/null
	@$(RM) $(OBJ_DEST) >/dev/null
	@$(PRINTF_CLEAN_MSG)

fclean: clean
	@$(MAKE) fclean -C ./libft >/dev/null
	@$(LIBFT_FCLEAN_MSG)
	@$(RM) $(NAME) >/dev/null
	@$(RM) $(ARCHIVE_DEST) >/dev/null
	@$(PRINTF_FCLEAN_MSG)

re: fclean all

git:
	@git remote set-url origin https://github.com/t0mmusic/ft_printf.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

.PHONY: all clean fclean re
