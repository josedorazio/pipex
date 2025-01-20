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

NAME = libft.a

#  find *.c | xargs echo

SRCS = src/ft_atoi.c src/ft_bzero.c src/ft_calloc.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c \
	src/ft_isprint.c src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c src/ft_memset.c \
	src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c \
	src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c \
	src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c src/ft_toupper.c 

SRCS_BONUS = src/ft_lstadd_back_bonus.c src/ft_lstadd_front_bonus.c src/ft_lstclear_bonus.c src/ft_lstdelone_bonus.c \
	src/ft_lstiter_bonus.c src/ft_lstlast_bonus.c src/ft_lstmap_bonus.c src/ft_lstnew_bonus.c src/ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean bonus

.PHONY: all clean fclean re
