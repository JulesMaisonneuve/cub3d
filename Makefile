NAME = cub3d

SRCS = window.c \
		main.c \
		../getnl/get_next_line_utils.c \
		../getnl/get_next_line.c \
		error.c \
		free_map.c \
		check_file.c \
		ft_strchrr.c \
		parse_player.c \
		draw_rectangle.c \
		hooks.c

OBJS = $(addprefix srcs/,$(SRCS:.c=.o))

CC = clang

CFLAGS = -Wall -Wextra -Werror

MLX = -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C mlx_linux
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)
	@echo "\033[32m[ ./cub3d created ]"

clean:
	$(RM) $(OBJS)
	make -C mlx_linux clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
