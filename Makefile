#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpfeffer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 17:50:14 by jpfeffer          #+#    #+#              #
#    Updated: 2017/04/24 17:58:15 by jpfeffer         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

LS = ft_ls

C_FILES = ft_ls.c

LIBFT		=	./libft/libft.a
PRINTF		=	./libraries/ft_printf/libftprintf.a
GNL			=	./libraries/get_next_line/libgnl.a
LIBLINK		=	-L ./libraries -lfdf
LIBRARY		=	./libraries/libfdf.a

SRCS = $(C_FILES)

C_FLAGS = -Wall -Werror -Wextra

.PHONY: all library libft printf gnl test clean cleanmlx fclean re

all: library $(LS)

library: libft printf gnl $(LIBRARY)

$(LIBRARY):
	@libtool -static -o ./libraries/libfdf.a $(LIBFT) $(PRINTF) $(GNL)

libft: $(LIBFT)

$(LIBFT):
	@make -C ./libft

printf: $(PRINTF)

$(PRINTF):
	@make -C ./libraries/ft_printf

gnl: $(GNL)

$(GNL):
	@make -C ./libraries/get_next_line

$(LS):
	@gcc $(C_FLAGS) $(LIBLINK) $(SRCS) -o ft_ls

test: fclean library
	@gcc $(SRCS) $(LIBLINK) $(FRAMEWORK) main.c -o ft_ls

ftest: fclean library
	@gcc $(SRCS) $(LIBLINK) $(FRAMEWORK) -fsanitize=address main.c -o ft_ls

clean:
	@make clean -C ./libft
	@make clean -C ./libraries/ft_printf
	@make clean -C ./libraries/get_next_line

fclean: clean
	@rm -f $(PUSH_SWAP) $(CHECKER) $(LIBRARY) a.out ft_ls
	@make fclean -C ./libft
	@make fclean -C ./libraries/ft_printf
	@make fclean -C ./libraries/get_next_line

re: fclean all