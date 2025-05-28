# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRCS = main.c cmd_parse.c execute.c path_utils.c execute_utils.c path_utils2.c \
       printf/ft_printf.c printf/printf_utils.c printf/ft_printf_hex.c printf/ft_pointersp.c
OBJS = $(SRCS:.c=.o)

# Library paths
LIBFT_DIR = ../LibftDamaga
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR) -Iprintf

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re