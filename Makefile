# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davidma2 <davidma2@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 15:07:00 by davidma2          #+#    #+#              #
#    Updated: 2025/05/28 15:08:15 by davidma2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c printf_utils.c ft_printf_hex.c ft_pointersp.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re