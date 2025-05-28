# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davidma2 <davidma2@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 15:30:00 by davidma2          #+#    #+#              #
#    Updated: 2025/05/28 15:16:00 by davidma2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = pipex

# Source files
SRCS = main.c \
       execute.c \
       execute_utils.c \
       path_utils.c \
       path_utils2.c \
       cmd_parse.c \
       parse_args.c

OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT_DIR = ../LibftDamaga
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Include directories
INCLUDES = -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR)

# Linking libraries
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@echo "Compiling ft_printf..."
	@make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean

re: fclean all

test: $(NAME)
	@echo "Testing pipex with basic commands..."
	@echo "Testing: echo hello | cat"
	@echo "hello world" > test_input.txt
	@./$(NAME) test_input.txt "cat" "wc -l" test_output.txt
	@echo "Expected: 1"
	@echo "Got:"
	@cat test_output.txt
	@rm -f test_input.txt test_output.txt

.PHONY: all clean fclean re test