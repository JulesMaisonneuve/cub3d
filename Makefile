NAME = cub3d

SRCS = window.c \
		init.c \
		main.c \
		../getnl/get_next_line_utils.c \
		../getnl/get_next_line.c \
		check_errors.c \
		print_error.c \
		free_map.c \
		check_file.c \
		check_map.c \
		get_player_infos.c \
		get_cubfile_infos.c \
		draw_column.c \
		key_hooks.c \
		set_wall_orientation.c \
		ray_casting.c \
		textures.c \
		ft_split.c \
		cub3d_utils.c \
		cub3d_utils2.c \
		trgb.c \
		player_movements.c \
		camera_rotation.c \
		weapon.c

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
