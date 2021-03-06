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

C_FILES = ft_ls.c path.c sort.c arguments.c hidden.c print.c print2.c xattr.c \
utility.c directories.c time.c scale.c

LIBFT		=	./libft/libft.a
PRINTF		=	./libraries/ft_printf/libftprintf.a
LIBLINK		=	-L ./libraries -lls
LIBRARY		=	./libraries/libls.a

SRCS = $(C_FILES)

C_FLAGS = -Wall -Werror -Wextra

.PHONY: all library libft printf test clean cleanmlx fclean o

all: library $(LS)

library: libft printf $(LIBRARY)

$(LIBRARY):
	@libtool -static -o ./libraries/libls.a $(LIBFT) $(PRINTF)

libft: $(LIBFT)

$(LIBFT):
	@make -C ./libft

printf: $(PRINTF)

$(PRINTF):
	@make -C ./libraries/ft_printf

$(LS): $(C_FILES) ft_ls.h
	@gcc $(C_FLAGS) $(LIBLINK) $(SRCS) -o ft_ls

test: fclean library
	@gcc $(SRCS) $(LIBLINK) $(FRAMEWORK) -o ft_ls

ftest: fclean library
	@gcc $(SRCS) $(LIBLINK) $(FRAMEWORK) -fsanitize=address -o ft_ls

clean:
	@make clean -C ./libft
	@make clean -C ./libraries/ft_printf

fclean: clean
	@rm -f $(PUSH_SWAP) $(CHECKER) $(LIBRARY) a.out ft_ls
	@make fclean -C ./libft
	@make fclean -C ./libraries/ft_printf

o: fclean all