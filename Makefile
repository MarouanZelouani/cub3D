NAME = cub3D
CC = cc -Wall -Wextra -Werror -g
# SRC = $(wildcard src/*.c parsing/*.c)
SRC = 	src/3D_map.c \
		src/collisions.c \
		src/dda.c src/hook.c \
		src/main.c \
		src/minimap.c \
		src/move.c \
		src/ray.c \
		src/textures.c \
		parsing/map_parsing.c \
		parsing/parsing2.c \
		parsing/parsing.c \
		parsing/rgb.c \
		parsing/space.c \
		parsing/tool.c \
		parsing/tools2.c \
		parsing/validation.c \
		parsing/zero.c

OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(OBJ) $(LIB) libmlx.a -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -I/usr/include -O3 -c $< -o $@
	
clean:
	make -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all
