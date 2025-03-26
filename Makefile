NAME = cub3D
CC = cc -Wall -Werror -Wextra -ggdb 
SRC = parsing/map_parsing_2.c\
		parsing/map_parsing.c\
		parsing/parsing2.c\
		parsing/parsing.c\
		parsing/rgb.c\
		parsing/space.c\
		parsing/tools2.c\
		parsing/tools3.c\
		parsing/tools.c\
		parsing/validation.c\
		parsing/zero.c\
		src/3D_map.c\
		src/collisions.c\
		src/dda.c\
		src/hook.c\
		src/main.c\
		src/minimap.c\
		src/move.c\
		src/ray.c\
		src/textures.c

OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	$(CC) $(OBJ) $(LIB) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra  -I/usr/include -Imlx_linux -c $< -o $@
	
clean:
	make -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all
