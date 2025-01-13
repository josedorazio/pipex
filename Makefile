# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2024/09/28 15:48:26 by jdorazio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PIPEX.a

#  find *.c | xargs echo

SRCS =  src/main.c src/utils.c
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g


all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -rf src/*.o
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft 

re: fclean bonus

.PHONY: all clean fclean re
